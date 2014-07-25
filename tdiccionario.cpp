// Class automatically generated by Dev-C++ New Class wizard
#include "tdiccionario.h" // class's header file

// class constructor
TDiccionario::TDiccionario(char *ruta) : abrir_fichero()
{
    objTraza = new traza();
    objTraza->setTraza("TDiccionario Inicio");

    string = new TCString();
    stringLineasIndex = new TClist();

    objTraza->setTraza("Strings y lista creados");
    char dirParseo[255];
    strcpy(dirParseo, ruta);
    char dirIndex[255];
    strcpy(dirIndex, ruta);


    #ifdef GP2X
        strcat(dirParseo,"/dic/parseo.txt");
        strcat(dirIndex,"/dic/index.txt");
        strcpy(filename,dirParseo);
        strcpy(fileIndex,dirIndex);
        objTraza->print("TDiccionario: Strings creados",filename);
        objTraza->print("TDiccionario: Strings creados",dirIndex);
    #else
        strcat(dirParseo,"\\dic\\parseo.txt");
        strcat(dirIndex,"\\dic\\index.txt");
        strcpy(filename,dirParseo);
        strcpy(fileIndex,dirIndex);
    #endif

    numLineasIndex = 0;
    objTraza->setTraza("TDiccionario Antes de crear index");
    cargarIndex();
    this->texto = NULL;
    objTraza->setTraza("TDiccionario END");

}

TDiccionario::~TDiccionario()
{
    free(offsetLineasIndex);
    delete stringLineasIndex;
    delete string;
}

int TDiccionario::find(char *dato)
{

    int posicion = -1;

    if (dato != NULL)
    {
        posicion = stringLineasIndex->find(dato);
        if (posicion >= 0)
        {
            procesar_linea_fichero(posicion);
            formatear();
        }
    }
    return posicion;
}

int TDiccionario::findAprox(char *dato,TClist *datosSalida)
{

    int posicion = -1;
    string->toLowerCase(dato);


    if (dato != NULL)
    {
        posicion = stringLineasIndex->findAprox(dato,datosSalida);
        if (posicion >= 0)
        {
            procesar_linea_fichero(posicion);
            formatear();
        }
    }
    return posicion;
}

char * TDiccionario::get()
{
    return string->get();
}

void TDiccionario::formatear()
{
    int tam = strlen( this->texto );

    int maxLetras = 512;
    char lema[maxLetras];
    memset(lema, '\0', maxLetras);
    bool tagLema = false;
    bool tagContLema = false;
    bool tagAcep = false;
    bool tagComp = false;
    char acepcion[maxLetras];
    memset(acepcion, '\0', maxLetras);
    char textoFormateado[5000];
    strcpy(textoFormateado,"");

    int posLema = 0;
    int posAcep = 0;

    int inicio = 0;
    bool tagIni = false;
    bool tagFin = false;

    string = new TCString();


    if ( this->texto != NULL)
    {
        do
        {
            while (this->texto[inicio] != '<' && inicio < tam && !tagIni)
            {
                inicio++;
                if (this->texto[inicio] != '<' && this->texto[inicio] != '>')
                {
                    acepcion[posAcep] = this->texto[inicio];
                    posAcep++;
                }
            }

            tagIni = true;
            inicio++;

            if (this->texto[inicio] != '>')
            {
                lema[posLema] = this->texto[inicio];
                posLema++;

                //Recogemos lo que hay entre < ___ >
                if (lema[0] == 'l')
                {
                    tagLema = true;
                }

                //Recogemos lo que hay entre > ___ <
                if (posLema > 1)
                {
                    if (lema[0] == '/'  && lema[1] == 'l')
                    {
                        tagContLema = true;
                    }

                    if (lema[0] == '/'  && lema[1] == 'a' )
                    {
                        tagAcep = true;
                    }
                    else if (lema[0] == '/'  && lema[1] == 'c' )
                    {
                        tagComp = true;
                    }
                }
            }

            if (this->texto[inicio] == '>')
            {
                string->trim(lema);
                if (tagLema)
                {
                    //printf("lema: %s\n",lema);
                    //lema[0] = ' ';
                    //string->trim(lema);

                    //string->add(lema);string->add("\n");
                    //strcat(textoFormateado,lema);
                    //strcat(textoFormateado,"\n");
                }
                if (tagComp)
                {
                    //printf("comp: %s\n",acepcion);
                    //strcat(textoFormateado,acepcion);
                    //strcat(textoFormateado,"\n");
                    string->add(acepcion);string->add("\n");
                }
                else if (tagAcep)
                {
                    //printf("acep: %s\n",acepcion);
                    //strcat(textoFormateado,acepcion);
                    //strcat(textoFormateado,"\n");
                    string->add(acepcion);string->add("\n");
                }
                else if (tagContLema)
                {
                    //printf("contLema: %s\n",acepcion);
                    //strcat(textoFormateado,acepcion);
                    //strcat(textoFormateado,"\n");
                    string->add(acepcion);string->add("\n");
                }

                tagIni = false;
                tagFin = true;
                tagLema = false;
                tagAcep = false;
                tagComp = false;
                tagContLema = false;
                posLema = 0;
                posAcep = 0;
                memset(lema, '\0', maxLetras);
                memset(acepcion, '\0', maxLetras);
            }
        }
        while (inicio < tam);

        //printf("texto\n%s",textoFormateado);
        //printf("texto-------------\n%s",string->get());
        //printf("------------------\n");
    }


}

bool TDiccionario::procesar_linea_fichero(int linea)
{
    FILE* fin;
    long tam = 0;
    long inicio = 0;

    if (linea < numLineasIndex)
    {
        if (this->Gettexto() != NULL)
            delete [] texto;

        if ((fin = fopen(filename,"rb"))==NULL)
        {
            printf("Se ha producido un error al abrir el fichero\n");
            return false;
        }
        else
        {
            //tam = this->getSize(fin);
            if (linea > 0)
            {
                tam = offsetLineasIndex[linea] - offsetLineasIndex[linea-1];
                inicio = offsetLineasIndex[linea-1]-2;
            }
            else
            {
                tam = offsetLineasIndex[0];
                inicio = 0;
            }

            if (this->texto != NULL) delete this->texto;
            this->texto = new char[tam+1];
            memset(this->texto, '\0', tam+1);
            fseek(fin,inicio*sizeof(char),SEEK_SET);
            fread(this->texto, 1, tam, fin);
            printf("TEXTO: %s\n",this->texto);
            fclose(fin);
            return true;

        }
    }
    return false;
}

int TDiccionario::cargarIndex()
{
    FILE* finIndex;
    char * textoIndex = NULL;
    int tamIndex;
    char numero [20] = {""};
    char palabra [255] ={""};
    int contadorCifras = 0;
    int contadorLetras = 0;
    bool startPalabra = false;

	if (textoIndex != NULL)
	    delete [] textoIndex;

	if ((finIndex = fopen(fileIndex,"rb"))==NULL)
	{
        printf("Se ha producido un error al abrir el fichero\n");
        return false;
    }
    else
    {
        tamIndex = this->getSize(finIndex);
        textoIndex = new char[tamIndex+1];
        memset(textoIndex, 0, tamIndex+1);
        fread(textoIndex, 1, tamIndex, finIndex);
        fclose(finIndex);

        for (int i=0;i<tamIndex;i++)
        {
            if (i == tamIndex-1)
            {
                if (textoIndex[i] == '_')
                {
                    if (numLineasIndex == 0)
                    {
                        offsetLineasIndex = (int *) malloc(sizeof(int));
                    }
                    else
                    {
                        offsetLineasIndex = (int *) realloc(offsetLineasIndex,(numLineasIndex+1)*sizeof(int));
                    }

                    offsetLineasIndex[numLineasIndex] = atoi(numero)+2;

                    numLineasIndex++;
                    startPalabra = true;
                    memset(palabra,'\0',255);
                }
                else if (startPalabra)
                {
                    palabra[contadorLetras] = textoIndex[i];
                    contadorLetras++;
                }
            }
            else
            {
                if (textoIndex[i] == '_')
                {
                    if (numLineasIndex == 0)
                    {
                        offsetLineasIndex = (int *) malloc(sizeof(int));
                    }
                    else
                    {
                        offsetLineasIndex = (int *) realloc(offsetLineasIndex,(numLineasIndex+1)*sizeof(int));
                    }

                    offsetLineasIndex[numLineasIndex] = atoi(numero)+2;

                    numLineasIndex++;
                    startPalabra = true;
                    memset(palabra,'\0',255);
                }
            }

            //En numero vamos almacenando el string de cada cifra que luego convertiremos
            numero[contadorCifras] = textoIndex[i];

            if (i == tamIndex-1)
            {
                if (((int)textoIndex[i] == 13 || (int)textoIndex[i+1] == 10))
                {
                    contadorCifras = 0;
                    startPalabra = false;
                    contadorLetras = 0;
                    stringLineasIndex->add(palabra);
                }
            }
            else if ((int)textoIndex[i] == 13 && (int)textoIndex[i+1] == 10)
            {
                contadorCifras = 0;
                startPalabra = false;
                contadorLetras = 0;
                stringLineasIndex->add(palabra);
            }
            else
            {
                if (startPalabra && textoIndex[i] != '_')
                {
                    palabra[contadorLetras] = textoIndex[i];
                    contadorLetras++;
                }
                contadorCifras++;
            }
        }
        //guardarOrden(stringLineasIndex);
        return true;

    }
}

void TDiccionario::guardarOrden (TClist *lista)
{
    int tam = lista->size();
    lista->Sort();

    printf("tam: %d\n",tam);

    FILE* fout;

    if ( (fout = fopen("C:\\Documents and Settings\\DicRAE\\RAEDump\\salida.txt","wt")) != NULL)
    {

    for (int i=0;i<tam;i++)
    {
        fwrite(lista->get(i), sizeof(char) , strlen(lista->get(i)), fout);
        fwrite("\n", sizeof(char) , strlen("\n"), fout);
    }

      fclose(fout);
    }
}