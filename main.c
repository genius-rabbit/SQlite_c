#include  <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>

static int callback(void *NotUsed,int argc,char **argv,char **azColName){
    int i;
    for(i=0;i<argc;i++){
        printf("%s=%s\n",azColName[i],argv[i]? argv[i]:NULL);
    }
    printf("\n");
    return 0;
}

int main() {
    sqlite3 *db;
    char *ErrMsg=0;
    int rc;
    char *sql;
    const char *data;
    data = "Callback function called";

    rc=sqlite3_open("student.db",&db);

    if(rc){
        fprintf(stderr,"Can't open database:%s\n",sqlite3_errmsg(db));
    }else{
        fprintf(stdout,"Open database successfully\n");
    }

    //创建 SQL 语句
    sql = "CREATE TABLE STUDENT("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "NAME           TEXT    NOT NULL," \
         "AGE            INT     NOT NULL," \
         "ADDRESS        CHAR(50)," \
         "SCHOLARSHIP         REAL );";

    rc =sqlite3_exec(db,sql,callback,(void*)data,&ErrMsg);

    if(rc!=SQLITE_OK){
        fprintf(stderr,"SQL error:%s\n",ErrMsg);
        sqlite3_free(ErrMsg);
    }else{
        fprintf(stdout,"Table created successfully\n");
    }

    //创建记录
    sql = "INSERT INTO STUDENT (ID,NAME,AGE,ADDRESS,SCHOLARSHIP) "  \
         "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
         "INSERT INTO STUDENT (ID,NAME,AGE,ADDRESS,SCHOLARSHIP) "  \
         "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
         "INSERT INTO STUDENT (ID,NAME,AGE,ADDRESS,SCHOLARSHIP)" \
         "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
         "INSERT INTO STUDENT (ID,NAME,AGE,ADDRESS,SCHOLARSHIP)" \
         "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

    //Excute SQL statement
    rc =sqlite3_exec(db,sql,callback,(void*)data,&ErrMsg);

    //查找操作
    sql = "SELECT * from STUDENT";
    rc =sqlite3_exec(db,sql,callback,(void*)data,&ErrMsg);

    //更新操作
    /* Create merged SQL statement */
    sql = "UPDATE COMPANY set SALARY = 25000.00 where ID=1; " \
         "SELECT * from COMPANY";

    //删除操作
    /* Create merged SQL statement */
    sql = "DELETE from COMPANY where ID=2; " \
         "SELECT * from COMPANY";


    sqlite3_close(db);
    return 0;
}