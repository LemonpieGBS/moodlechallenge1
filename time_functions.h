#include <ctime>

time_t now = time(0);
tm *ltm = localtime(&now);

// Estas son funciones que obtienen el tiempo usando la libreria ctime y el UNIX timestamp
// que el unix es una cosa que va contando cada segundo desde 1 de enero 1970 que quieren que les diga
// gracias a esta pagina que es donde saque las convalencias:
// https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm

// Asi no me pueden engañar cambiando la fecha de su computador CABRONES

void update_timer() { now = time(0); ltm = localtime(&now); }

int get_current_year() { update_timer(); return (1900 + ltm->tm_year); }
int get_current_month() { update_timer(); return (1 + ltm->tm_mon); }
int get_current_day() { update_timer(); return (ltm->tm_mday); }
int get_current_hour() { update_timer(); return (ltm->tm_hour); }
int get_current_minute() { update_timer(); return(ltm->tm_min); }
int get_current_second() { update_timer(); return(ltm->tm_sec); }

int get_unix_year(time_t unix) { ltm = localtime(&unix); return (1900 + ltm->tm_year); }
int get_unix_month(time_t unix) { ltm = localtime(&unix); return (1 + ltm->tm_mon); }
int get_unix_day(time_t unix) { ltm = localtime(&unix); return (ltm->tm_mday); }
int get_unix_hour(time_t unix) { ltm = localtime(&unix); return (ltm->tm_hour); }
int get_unix_minute(time_t unix) { ltm = localtime(&unix); return(ltm->tm_min); }
int get_unix_second(time_t unix) { ltm = localtime(&unix); return(ltm->tm_sec); }