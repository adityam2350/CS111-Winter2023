#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

typedef uint32_t u32;
typedef int32_t i32;

struct process
{
  u32 pid;
  u32 arrival_time;
  u32 burst_time;


  TAILQ_ENTRY(process) pointers;

  /* Additional fields here */
  u32 recent_cpu;
  bool waiting_first;
  /* End of "Additional fields here" */
};

TAILQ_HEAD(process_list, process);

u32 next_int(const char **data, const char *data_end)
{
  u32 current = 0;
  bool started = false;
  while (*data != data_end)
  {
    char c = **data;

    if (c < 0x30 || c > 0x39)
    {
      if (started)
      {
        return current;
      }
    }
    else
    {
      if (!started)
      {
        current = (c - 0x30);
        started = true;
      }
      else
      {
        current *= 10;
        current += (c - 0x30);
      }
    }

    ++(*data);
  }

  printf("Reached end of file while looking for another integer\n");
  exit(EINVAL);
}

u32 next_int_from_c_str(const char *data)
{
  char c;
  u32 i = 0;
  u32 current = 0;
  bool started = false;
  while ((c = data[i++]))
  {
    if (c < 0x30 || c > 0x39)
    {
      exit(EINVAL);
    }
    if (!started)
    {
      current = (c - 0x30);
      started = true;
    }
    else
    {
      current *= 10;
      current += (c - 0x30);
    }
  }
  return current;
}

void init_processes(const char *path,
                    struct process **process_data,
                    u32 *process_size)
{
  int fd = open(path, O_RDONLY);
  if (fd == -1)
  {
    int err = errno;
    perror("open");
    exit(err);
  }

  struct stat st;
  if (fstat(fd, &st) == -1)
  {
    int err = errno;
    perror("stat");
    exit(err);
  }

  u32 size = st.st_size;
  const char *data_start = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (data_start == MAP_FAILED)
  {
    int err = errno;
    perror("mmap");
    exit(err);
  }

  const char *data_end = data_start + size;
  const char *data = data_start;

  *process_size = next_int(&data, data_end);

  *process_data = calloc(sizeof(struct process), *process_size);
  if (*process_data == NULL)
  {
    int err = errno;
    perror("calloc");
    exit(err);
  }

  for (u32 i = 0; i < *process_size; ++i)
  {
    (*process_data)[i].pid = next_int(&data, data_end);
    (*process_data)[i].arrival_time = next_int(&data, data_end);
    (*process_data)[i].burst_time = next_int(&data, data_end);
  }

  munmap((void *)data, size);
  close(fd);
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    return EINVAL;
  }
  struct process *data;
  u32 size;
  init_processes(argv[1], &data, &size);
  u32 quantum_length = next_int_from_c_str(argv[2]);

  struct process_list list;
  TAILQ_INIT(&list);

  u32 total_waiting_time = 0;
  u32 total_response_time = 0;

  
  /* Your code here */
 
  struct process* current_proc;

  int time=0;
  bool remove=false;
  bool add_back=false;
  u32 pid_running=-1;
  int i=0;
  u32 slice_left=quantum_length;
  u32 earliest_time=10000000;

  for (int i=0;i<size;i++)
  {
    if(earliest_time>data[i].arrival_time)
      {
	earliest_time=data[i].arrival_time;
      }
  }

  while(!TAILQ_EMPTY(&list) || time <= data[0].arrival_time)
  {
    //Adds processes to the process queue as they arrive
    for (int i=0;i<size;i++)
    {
      if(data[i].arrival_time==time)
      {
	 data[i].recent_cpu=data[i].arrival_time;
	 data[i].waiting_first=true;
	 //printf("Added: %zu at time %zu \n",data[i].pid,time);
         TAILQ_INSERT_TAIL(&list,&data[i],pointers); 	
      }
    }
    //Add the recently popped process back to the queue if it's burst time isn't complete
    if(remove)
    {
      current_proc->recent_cpu=time;
      TAILQ_REMOVE(&list,current_proc,pointers);
      //printf("Removed: %zu at time %zu \n",current_proc->pid,time);
      if(add_back)
      {
          TAILQ_INSERT_TAIL(&list,current_proc,pointers);
	  // printf("Added: %zu at time %zu \n",current_proc->pid,time);
      }
      slice_left=quantum_length;
    }
    remove=false;
    add_back=false;
    
    //If we haven't reached the first process yet, just keep going
    if(TAILQ_EMPTY(&list))
    {
      time++;
      continue;
    }
    
    //If this is the process just began on the CPU, we add it's waiting time for that period
    current_proc=TAILQ_FIRST(&list);
    pid_running=current_proc->pid;
      
    if(slice_left==quantum_length)
    {
      total_waiting_time=total_waiting_time+(time-(current_proc->recent_cpu));
    }
    
    //If this is the first time a process is on the CPU, we add it's response time to the total response time
    if(current_proc->waiting_first)
    {
      total_response_time=total_response_time+(time-(current_proc->arrival_time));
      current_proc->waiting_first=false;
    }
    
    //take down slice_left and burst time of the process
    current_proc->burst_time--;
    slice_left--;
    //if a process' burst time is now zero, we take it out of the queue for good
    
    if (current_proc->burst_time==0)
    {
      remove=true;
      add_back=false;
    }
    //if a slice is zero, we flag the process to be removed from the queue and added back on the next iteration 
    else if(slice_left==0)
    {
      remove=true;
      add_back=true;
    }
    time++;
  }
  /* End of "Your code here" */

  printf("Average waiting time: %.2f\n", (float)total_waiting_time / (float)size);
  
  printf("Average response time: %.2f\n", (float)total_response_time / (float)size);

  free(data);
  return 0;
}
