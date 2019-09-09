
/* date-time.c
 * ===========
 * this example shows some standard time functions behaviour
 * tento pøíklad testuje standardní funkce pro práci s èasem
 *
 * time ctime asctime mktime localtime strftime
 *
 * Warning - the locales should be installed 
 * Pozor - pøedpokládá nainstalované pøíslu¹né lokalizace
 *
 */
#include <stdio.h>
#include <time.h>
#include <locale.h>

int main() {
  char *l;
  time_t t;        /* time in seconds from epoch */
  struct tm *tm;   /* pointer to structure */
  char s[100];     /* buffer for strftime */
  l = setlocale(LC_TIME,""); /* try to set LC_TIME=cs_CZ in environment */
  if(l==NULL)
      return 1; /* can't set locale */
  t = time(NULL);
  printf("Current time:\n");
  printf("----------------------------------------\n");
  printf("time:       %ld\n", t);
  tm = localtime(&t);
  printf("localtime:  %s", asctime(tm));
  printf("----------------------------------------\n");
  printf("  tm_sec:     %d\n", tm->tm_sec);         /* seconds */
  printf("  tm_min:     %d\n", tm->tm_min);         /* minutes */
  printf("  tm_hour:    %d\n", tm->tm_hour);        /* hours */
  printf("  tm_mday:    %d\n", tm->tm_mday);        /* day of the month */
  printf("  tm_mon:     %d\n", tm->tm_mon);         /* month */
  printf("  tm_year:    %d\n", tm->tm_year);        /* year */
  printf("  tm_wday:    %d\n", tm->tm_wday);        /* day of the week */
  printf("  tm_yday:    %d\n", tm->tm_yday);        /* day in the year */
  printf("  tm_isdst:   %d\n", tm->tm_isdst);       /* daylight saving time */
  printf("----------------------------------------\n");
  printf("ctime:      %s", ctime(&t));
  printf("gmtime:     %s", asctime(gmtime(&t)));
  printf("mktime:     %ld\n", mktime(tm));
  printf("----------------------------------------\n");
  printf("tzname[0]:  %s\n", tzname[0]);
  printf("tzname[1]:  %s\n", tzname[1]);
  printf("timezone:   %ld\n", timezone);
  printf("daylight:   %d\n", daylight); /* possible DST */
  printf("----------------------------------------\n");
  /* user defined locale */
  strftime(s,sizeof(s),"%c",localtime(&t)); /* localized */
  printf("strftime,%-5s:  %s\n", l, s);

  l=setlocale(LC_TIME,"cs_CZ"); /* czech */
  strftime(s,sizeof(s),"%c",localtime(&t)); 
  printf("strftime,%-5s:  %s\n", l, s);

  l=setlocale(LC_TIME,"de_AT"); /* german in Austria */
  strftime(s,sizeof(s),"%c",localtime(&t));
  printf("strftime,%-5s:  %s\n", l, s);

  l=setlocale(LC_TIME,"fr_FR"); /* french */
  strftime(s,sizeof(s),"%c",localtime(&t));
  printf("strftime,%-5s:  %s\n", l, s);

  l=setlocale(LC_TIME,"C");     /* default locale */
  strftime(s,sizeof(s),"%c",localtime(&t));
  printf("strftime,%-5s:  %s\n", l, s);

  printf("----------------------------------------\n");
  return 0;
}

