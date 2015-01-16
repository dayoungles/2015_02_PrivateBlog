//
//  webserver.c
//
//
//  Created by Dayoungle on 2014. 11. 21..
//
//

#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>

#define BUF_SIZE 1024
#define SMALL_BUF 100

void* request_handler(void* arg);
void send_data(FILE* fp, char* ct, char* file_name);
char* content_type(char* file);
void send_error(FILE* fp);
void error_handeling(char* message);

int main(int argc, char* argv[]){
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    itn clnt_adr_size;
    char buf[BUF_SIZE];
    pthread_t t_id;
    
    if(argc!=2){
        printf("usage: %s <port> \n", argv[0]);
        exit(1);
    }
    
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]);
                              
                              if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
                              error_handling("bind() error");
                              if(listen(serv_sock, 2Q)==-1)
                              error_handling("listen() error");
                              
                              while(1) {
                                  clnt_adr_size=sizeof(clnt adr);
                                  clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_size); printF("Connection Request : %s:%d \n",
                                                                                                                   inet ntoa(c]nt_adr.sJn_addr), ntohs(clnt_adrosin_port));
                                  pthread create(&t i.d~ NUIL, request.handler, &clnt_sock);
                                  pthread detach(t_id);
                              }
                              close(serv sock);
                              return 0;
                              }
                              
                              void* request_handler(void *arg) (
                                                                int cint_sock=*((int*)arg);
                                                                char req_line[SMALL_BUF];
                                                                FILE* cInt_read;
                                                                FILE* clnt_write;
                                                                
                                                                char method[10];
                                                                char ct[15];
                                                                char file_name[30];
                                                                clnt_read=fdopen(clnt_sock, "r");
                                                                clnt_write=fdopen(dup(clnt_sock), "w"); fgets(req_line, SMALL_BUF, clnt_read);
                                                                
                                                                if(strstr(req_line, "HTTP/")==NULL) {
                                                                    send_error(clnt_write);
                                                                    fclose(clnt_read);
                                                                    fclose(clnt_write);
                                                                    return;
                                                                }
                                                                strcpy(method, strtok(req_line, " /"))j strcpy(file_name, strtok(NULL, " /"));
                                                                strcpy(ct, content_type(file_name));
                                                                
                                                                if(strcmp(method, "GET")!=0){
                                                                    send_error (clnt_write) ; 
                                                                    fclose(clnt_read) ; 
                                                                    fclose(clnt_write) ;
                                                                    return;
                                                                }
                                                                
                                                                fclose(clnt_read);
                                                                send_data(clnt_write, ct, file_name);
                                                                }
                                                                
                                                                void send_data(FILE* fp, char* ct, char* file_name){
                                                                    char protocol[] = "HTTP/1.0 200 OK\r\n";
                                                                    char server[] = "Server:Linux Web Server \r\n";
                                                                    char cnt_len[] "Content-length:2048\r\n";
                                                                    char cnt_type[SMALL_BUF];
                                                                    char buf[BUF_SIZE];
                                                                    FILE* send_file;
                                                                    
                                                                    sprintf(cnt_type, "Content-type:%s\r\n\r\n", ct); send_file=fopen(file_name, "r");
                                                                    if(send_file==NULL){
                                                                        send_error(fp);
                                                                        return;
                                                                    }
                                                                    
                                                                    fputs(protocol, fp); 
                                                                    fputs(server, fp);
                                                                    fputs(cnt_len, fp);
                                                                    fputs(cnt_type, fp);
                                                                    
                                                                    while(fgets(buf, BUF_SIZE, send_file)!=NULL){
                                                                        fputs(buf, fP); 
                                                                        fflush(fp);
                                                                    }
                                                                    fflush(fP);
                                                                    fclose(fP);
                                                                }
                                                                
                                                                char* content_type(char* file){
                                                                    char extension[SMALL_BUF]; 
                                                                    char flIe_name[SMALL_BUF]; 
                                                                    strcpy(file_name, file);
                                                                    strtok(file_name, "."); 
                                                                    strcpy(extension, strtok(NULL, "."));
                                                                    
                                                                    
                                                                    if(!strcmp(extension, "html") || !strcmp(extension, "htm"))
                                                                        return "text/html";
                                                                    else
                                                                        return "text/plain";
                                                                    
                                                                }
                                                                
                                                                
                                                                vold send_error(FILE* fp)
    {
        char protocol[]="HTTP/1.0 480 Bad Request\r\n";
        char server[]="Server:Llnux Web Server \r\n";
        char cnt_1en[]="Content-1ength:2048\r\n";
        char cnt_type[]="Content-type:text/html\r\n\r\n";
        char content[]="<html><head><tltle>NETWORK</tltle></head>" "<body><font slze=+5><br>_9_~r ~! ,q~ ~hL~ ~ ,q~ ~ ~_~! " "</font></body></html>";
        
        fputs(protocol, fp);
        fputs(server, fp); 
        fputs(cnt_len, fp);
        fputs(cnt_type, fp);
        fflush(fp);
    }
                                                                
                                                                vold error_handling(char* message) (
                                                                                                    fputs(message, stderr);
                                                                                                    fputc('\n', stderr); 
                                                                                                    exit(1);
                                                                                                    }
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
