#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    do
    {
        float V_fonct=0;
        float VitesseMinReel=10; // vitesse (m/s) min où l'on va commencer à baisser la fréquence sur la pompe
        float VitesseMaxReel=25;// vitesse (m/s) max de fonctionnement de la pompe (on baisse la fréquence jusqu'à cette valeur, au-delà la pompe est coupée)
        float CapteurMax=50;// valeur max (m/s) d'acquisition du capteur
        int VitesseMin=0;
        int VitesseMax=1574654654;
        float VitesseReel=450;
        int VitesseNum=0;
        float VitesseA=0;
        float Frequence=0;
        int FrequenceNum=0;

        // Insert code

        printf("donnez une valeur en ampere entre 4 et 20\n"); // Cette demande remplace la véritable acquisition du vent par le capteur
        scanf("%f",&VitesseA);
        printf("VitesseA= %fmA\n", VitesseA);

        VitesseNum=(int)((VitesseA-4)*255/16);//conversion de ampère à sortie du can(8bits?) => on simule ici la sortie du can
        printf("VitesseNum= %d\n", VitesseNum);


        VitesseReel= ((VitesseA-4)*CapteurMax/16); // conversion de ampère à m/s
        printf("VitesseReel= %fm/s\n", VitesseReel);


        VitesseMin=(int)((VitesseMinReel)*255/CapteurMax); //conversion de la vitesse min pour être comparée à la valeur du capteur en sortie de can(8bits?)
        VitesseMax=(int)((VitesseMaxReel)*255/CapteurMax); //conversion de la vitesse max pour être comparée à la valeur du capteur en sortie de can(8bits?)
        printf("VitesseMin= %d\nVitesseMax= %d\n", VitesseMin, VitesseMax);


        if((VitesseNum>=VitesseMin)&&(VitesseNum<=VitesseMax))// la fréquence de la pompe n'est variée qu'à cette condition
        {

            V_fonct=VitesseMax-VitesseMin;
            Frequence=50-((30/V_fonct)*(VitesseNum-VitesseMin));

        }


        if(VitesseNum>VitesseMax)// Si la vitesse du vent est supérieur à "VitesseMax" (paramétré avec VitesseMaxReel), la pompe s'arrête
        {
            Frequence=0; // il faudra rajouter un timer d'environ 5 mins pour éviter que la pompe ne s'allume et s'éteigne très vite si la vitesse du vent est aux alentours du seuil
        }

        if(VitesseNum<VitesseMin)// la fréquence de la pompe est à 50Hz en-dessous du seuil défini par VitesseMin (paramétrer VitesseMinReel)
        {
            Frequence=50;
        }

        FrequenceNum=Frequence*255./50.; // conversion de la fréquence en valeur numérique pour le cna (8bits?)

        printf("La frequence est de %fHz\n", Frequence);
        printf("La valeur de frequence envoyee sur le cna est %d\n", FrequenceNum);

    }
    while(1);

    return 0;
}
