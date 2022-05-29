#ifndef DEFINES_H
#define DEFINES_H

//#define POSTGRESQL
#define MYSQL
//#define PARAMS

#ifdef MYSQL
    #define FILENAME "./config/mysql.cfg"
    #define USER_REP UsersRepositoryMySQL
    #define CANVAS_REP CanvasRepositoryMySQL
    #define PARAMS_REP ParamsRepositoryMySQL
#else
    #define FILENAME "./config/default.cfg"
    #define USER_REP UsersRepository
    #define CANVAS_REP CanvasRepository
    #define PARAMS_REP ParamsRepository
#endif

#endif // DEFINES_H
