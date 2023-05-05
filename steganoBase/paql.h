#ifndef PAQL_H
#define PAQL_H

//PAQL YNOV BORDEAUX


//Classe : Première lettre en majuscule, si plusieurs mots, AbcdEfjg   / CamelCase

//Structure  : struct st_iot {} ;    st_iot thermostat_st;

//Enumeration ; enum enum_couleurs{BLEU, ROUGE} ;            enum_couleurs  colors; colors= BLEU;

//typedef st_iot  iot_t ; // nouveau type = suffix _t
typedef char        char_t;
typedef float       float32_t; /*!< float32_t:  float.          Ex: f32_var*/
typedef double      float64_t; /*!< float64_t:  double.         Ex: f64_var*/
typedef long double float92_t; /*!< float92_t:  long double.    Ex: f92_var*/
typedef int			int32_t;   /*!< int32_t:    int             Ex: s32_var*/
typedef unsigned int uint32_t; /*!< uint32_t:   unsigned int    Ex: u32_vat*/

//string    s_var;  //prefix d'un string avec s_


//pointer   uint32_t* u32_var_ptr   =  u32_var;   // suffix _ptr    pour les pointers

//fonction : infinitif et en anglais  en minuscule

//méthode : infinitif et en anglais  en minuscule

//Accesser: get/set + Première de la variable en majuscule


#endif // PAQL_H
