/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilin <emilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:51:55 by emilin            #+#    #+#             */
/*   Updated: 2024/08/15 13:15:14 by emilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#define NC	"\e[0m"
#define YELLOW	"\e[1;33m"
#define BYELLOW	"\e[1;33m"
#define RED	"\e[31m"
#define GREEN	"\e[32m"
#define TIMES_CNT 2000

void *thread_routine(void *data)
{
  pthread_t tid;
  unsigned int *count;
  unsigned int i;

  tid = pthread_self();
  count = (unsigned int *)data;
  printf("%sThread [%ld]: Count at thread start = %u.%s\n",
		YELLOW, tid, *count, NC);
	i = 0;
  while(i < TIMES_CNT)
  {
    (*count)++;
    i++;
  }
  printf("%sThread [%ld]: Final count = %u.%s\n",
		BYELLOW, tid, *count, NC);
  return(NULL);    
}

int main(void)
{

 pthread_t t1;
 pthread_t t2;
 unsigned int count;
 
  count = 0;
  printf("Main: Expected count is %s%u%s\n", GREEN, 
					2 * TIMES_CNT, NC);
  pthread_create(&t1,NULL,thread_routine, &count);
  printf("Main: Created first thread [%ld]\n", t1);
  pthread_create(&t2,NULL,thread_routine, &count);
  printf("Main: Created second thread [%ld]\n", t2);
  pthread_join(t1, NULL);
  printf("Main: Joining first thread [%ld]\n", t1);
  pthread_join(t2, NULL);
  printf("Main: Joining second thread [%ld]\n", t2);
  if (count != (2 * TIMES_CNT))
		printf("%sMain: ERROR ! Total count is %u%s\n", RED, count, NC);
	else
		printf("%sMain: OK. Total count is %u%s\n", GREEN, count, NC);
  return (0);
}
