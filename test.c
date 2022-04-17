#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/* Définition d'un ensemble de trois signaux */
#define NB_SIGNAUX 3
int signaux[NB_SIGNAUX]={SIGINT,SIGTERM,SIGHUP};

/* Tableaux de structure sigaction pour la sauvegarde
   des gestionnaires en place */ 
struct sigaction sauvegardes[NB_SIGNAUX];

int main(void)
{
  /* Masques de blocage de signaux */
  sigset_t masque;
  sigset_t anciens;
  sigset_t pendants;
 
  int i;

  struct sigaction pourIgnorer;

  /* Creation du masque contenant les trois signaux a bloquer
     On commence par créer un masque vide avec sigemptyset
     que l'on remplit ensuite avec sigaddset
  */
  sigemptyset(&masque);
  for (i=0;i<NB_SIGNAUX;i++)
    sigaddset(&masque,signaux[i]);

  /* Mise en place du masque avec sauvegarde de l'ancien masque 
     dans la variable anciens */

  sigprocmask(SIG_SETMASK,&masque,&anciens);

  /* On roupille 15 secondes, histoire de faire des misères au processus
     Tapper ^C, envoyer des signaux TERM et HUP ... */
  puts("Delai de grace 15 secondes");
  fflush(stdout);
  sleep(15);
  puts("Fin du delai de grace");
  fflush(stdout);

  /* On recupere la liste des signaux pendants */
  sigpending(&pendants);

  /* Decodage (bestial) des signaux pendants */
  for (i=1;i<NSIG;i++)
    if (sigismember(&pendants,i))
      printf("Signal %d pendant bloque\n",i);

  /* On installe des gestionnaires << ignorer >> sur notre masque avant le deblocage 
       La première étape consiste à remplir les structures sigaction*/

  /* Pas de signaux particulier a bloquer pendant SIG_IGN 
     Theoriquement, ce parametre n'est pas pris en compte pour SIG_IGN
     mais on ne sait jamais */
  sigemptyset(&pourIgnorer.sa_mask);

  /* Mise a zero du champ sa_flags, theoriquement il est ignore, 
     mais on ne sait jamais */
  pourIgnorer.sa_flags=0;

  /* Pour chaque signal du tableau, on met en place un gestionnaire SIG_IGN
     Sans oublier de sauvergarder l'ancien gestionnaire dans le tableau de
     structures prevu a cet egard. */
  for (i=0;i<NB_SIGNAUX;i++)
    sigaction(signaux[i],&pourIgnorer,sauvegardes+i);

  /* L'ancien masque est remis en place */
  sigprocmask(SIG_SETMASK,&anciens,0);

  /* Ainsi que les anciens gestionnaires */
  for (i=0;i<NB_SIGNAUX;i++)
  {
    pourIgnorer.sa_handler=SIG_IGN;
    sigaction(signaux[i],sauvegardes+i,0);
  }

  return 0;
}
