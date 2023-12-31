// Class automatically generated by Dev-C++ New Class wizard

#include "traza.h" // class's header file


// class constructor
traza::traza(char *ruta)
{
    // insert your code here

    strcpy(this->ruta,ruta);
    this->setTraza(false);
}

traza::traza()
{
    // insert your code here

    #ifdef GP2X
    strcpy(this->ruta,"/mnt/sd/traza.txt");
    #else
    strcpy(this->ruta,"C:\\Users\\Daniel\\Documents\\traza.txt");
    #endif

    this->setTraza(false);


}


// class destructor
traza::~traza()
{
    // insert your code here
    fclose(this->fout);

}

void traza::print(char *msg,char *msg2)
{

    if (pintarTrazas == true)
    {
        char msg_2[850];

        if ( (this->fout = fopen(ruta,"at+")) != NULL)
        {
            strcpy(msg_2,msg);
            strcat(msg_2,": ");
            strcat(msg_2,msg2);
            strcat(msg_2,"\r\n");
            fwrite(msg_2, sizeof(char) , strlen(msg_2), this->fout);
            fclose(this->fout);
        }
    }

}

void traza::print(char *msg,int msg2)
{

    if (pintarTrazas == true)
    {
        char msg_2[850];
        char msg3[20];
        //char formato [] = {"%d"};

        sprintf(msg3,"%d",msg2);

        if ( (this->fout = fopen(ruta,"at+")) != NULL)
        {
            strcpy(msg_2,msg);
            strcat(msg_2,": ");
            strcat(msg_2,msg3);
            strcat(msg_2,"\r\n");
            fwrite(msg_2, sizeof(char) , strlen(msg_2), this->fout);
            fclose(this->fout);
        }
    }

}


void traza::print(char *msg)
{

    if (pintarTrazas == true)
    {
        char msg_2[850];
        //time_t timer;
        //struct tm *tblock;

        if ( (this->fout = fopen(ruta,"at+")) != NULL)
        {
            //timer = time(NULL);

            //tblock = localtime(&timer);

            strcpy(msg_2,msg);
            /*strcat(msg_2,": ");
            strcat(msg_2,asctime(tblock));
            strcat(msg_2,"\n");
*/

            strcat(msg_2,"\r\n");
            fwrite(msg_2, sizeof(char) , strlen(msg_2)-1, this->fout);
            fclose(this->fout);
        }
    }

}

void traza::setTraza(bool estado)
{
    this->pintarTrazas = estado;
}
