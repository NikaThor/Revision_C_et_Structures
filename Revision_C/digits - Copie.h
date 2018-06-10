/** 
 -------------------------------------------------------------------------
 @brief  Fichier d'entete des matrices des chiffres , '+' et '-'.
 @file   digits.h
 @autor  Dimitri Lambert , Haibo Lu
 @date   03 Mai 2018
 @remarks  MinGw-g++ 6.3.0
 -------------------------------------------------------------------------
 */

#ifndef DIGITS_H
#define DIGITS_H
// constantes
#define MAX_LIGNE 8
#define MAX_COLONNE 9
// 9 colonnes car chaque ligne d’une matrice
// contient implicitement un caractère ‘\0’
// matrice pour la représentation des digits
typedef char t_matrice [MAX_LIGNE][MAX_COLONNE];
const t_matrice digitPlus = {
    "        ",
    "        ",
    "    #   ",
    "    #   ",
    " ###### ",
    "    #   ",
    "    #   ",
    "        "
};
const t_matrice digitMoins = {
    "        ",
    "        ",
    "        ",
    "        ",
    " ###### ",
    "        ",
    "        ",
    "        "
};
const t_matrice digitZero = {
    "  ####  ",
    " #    # ",
    " #    # ",
    " #    # ",
    " #    # ",
    " #    # ",
    " #    # ",
    "  #### "
};
const t_matrice digitUn = {
    "     #  ",
    "    ##  ",
    "   # #  ",
    "     #  ",
    "     #  ",
    "     #  ",
    "     #  ",
    "     #  "
};
const t_matrice digitDeux = {
    "  ####  ",
    " #    # ",
    "      # ",
    "     #  ",
    "    #   ",
    "   #    ",
    "  #     ",
    " ###### "
};
const t_matrice digitTrois = {
    "  ####  ",
    " #    # ",
    "     #  ",
    "   ##   ",
    "     #  ",
    "      # ",
    " #    # ",
    "  ####  "
};
const t_matrice digitQuatre = {
    "     #  ",
    "    ##  ",
    "   # #  ",
    "  #  #  ",
    " ###### ",
    "     #  ",
    "     #  ",
    "     #  "
};
const t_matrice digitCinq = {
    " ###### ",
    " #      ",
    " #      ",
    " #####  ",
    "      # ",
    "      # ",
    " #    # ",
    "  ####  "
};
const t_matrice digitSix = {
    "  ####  ",
    " #    # ",
    " #      ",
    " #####  ",
    " #    # ",
    " #    # ",
    " #    # ",
    "  ####  "
};
const t_matrice digitSept = {
    " ###### ",
    "      # ",
    "     #  ",
    "   #### ",
    "    #   ",
    "   #    ",
    "  #     ",
    " #      "
};
const t_matrice digitHuit = {
    "  ####  ",
    " #    # ",
    " #    # ",
    "  ####  ",
    " #    # ",
    " #    # ",
    " #    # ",
    "  ####  "
};
const t_matrice digitNeuf = {
    "  ####  ",
    " #    # ",
    " #    # ",
    "  ##### ",
    "      # ",
    "      # ",
    " #    # ",
    "  ####  "
};

#endif /* DIGITS_H */

