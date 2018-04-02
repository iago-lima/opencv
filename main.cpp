/*******************************************************
*                                                      *
*   Criado em: Seg 26/Mar/2018,  09:12 hs              *
*   Instituicao: Universidade Federal do Ceará         *
*   Autor: Iago O. Lima                                *
*   email: iago.oliveira@alu.ufc.br                    *
*                                                      *
********************************************************/

//Código que captura as imagens utilizando a Webcam do computador.

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void drawText(Mat & image)
{
    putText(image, "Teste 2 - 26/03/18",
            Point(20, 50),
            FONT_HERSHEY_COMPLEX, 1, // Fonte e tamanho
            Scalar(0, 0, 0), // Cor da fonte
            2, LINE_AA); // Espessura da letra
}

int main()
{
    cout << "Built with OpenCV " << CV_VERSION << endl;
    Mat image; //
    VideoCapture capture;
    capture.open(0); //Configurando para obter as imagens da webcam
    CascadeClassifier face_cascade; //Criando classificador
    face_cascade.load("/opt/opencv/data/haarcascades/haarcascade_frontalface_alt2.xml"); //Carregando classificador fornecido pela OpenCV
   if(capture.isOpened()){ //Testando se conseguiu abrir a webcam
        cout << "Capturando" << endl;
        for(;;){
            capture >> image; //capturando imagem
            
            if(image.empty()){
                break;
            }
            vector<Rect> faces; //frames do rosto
            face_cascade.detectMultiScale(image, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(140, 140)); //Detectando rosto
            
            //Circulando rostos detectados
            for(int i = 0; i < (int)faces.size(); i++ ){
                Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
                ellipse(image, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 0, 255, 255 ), 4, 8, 0 );
            }
            drawText(image);// Jogando texto na tela
            imshow("Teste 2", image); //Jogando imagem 
            if(waitKey(10) >= 0) //Exibe um frame a cada 10ms e caso pressione uma tecla, encerra o programa
                break;
        }
    }
    else //Caso não consigo utilizar a webcam
    {
        cout << "Não Capturando" << endl;
        image = Mat::zeros(480, 640, CV_8UC1);
        drawText(image);
        imshow("Teste 2", image);
        waitKey(0);
    }
    return 0;
}


