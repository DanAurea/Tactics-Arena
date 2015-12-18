/**
 @file grid.h
 @brief En-tête gestion de la grille
 @author Cousin Brandon Chaudemanche Ewen Biardeau Tristan
 @version v1.00
 @date 18/12/2015
 */

#define RB "\e(0\x6a\e(B" /**< 188 Right Bottom corner */
#define RT "\e(0\x6b\e(B" /**< 187 Right Top corner */
#define LT "\e(0\x6c\e(B" /**< 201 Left Top cornet */
#define LB "\e(0\x6d\e(B" /**< 200 Left Bottom corner */
#define VL "\e(0\x78\e(B" /**< 186 Vertical Line */
#define HL "\e(0\x71\e(B" /**< 205 Horizontal Line */

void gridDisp(); /**< Affiche la grille */