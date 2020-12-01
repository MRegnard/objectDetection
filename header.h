#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <math.h>

#define TAILLE_MAX       10000 
#define NAME_MAX         50 
#define E34_MAX          16 
#define F0_MAX           128 
#define GDF_MAX          100 
#define METHOD_MAX       100 
#define SA_MAX           90 
#define FILE_NUMBER      10000 
#define CLASS_NUMBER     9 
#define TRAINNING_NUMBER 11
#define K 6

enum method {E34 , F0 , GDF , SA} ;

/*
const char* CLASS_1 = "s01";
const char* CLASS_2 = "s02";
const char* CLASS_3 = "s03";
const char* CLASS_4 = "s04";
const char* CLASS_5 = "s05";
const char* CLASS_6 = "s06";
const char* CLASS_7 = "s07";
const char* CLASS_8 = "s08";
const char* CLASS_9 = "s09";
*/
//enum class {S01,S02,S03,S04,S05,S06,S07,S08,S09}
/*
struct product{
	char name;
	char *method;
	float data[E34_MAX];
};*/
typedef int (*compfn)(const void*, const void*);

struct training_class{
	char *name;
	struct object* element[CLASS_NUMBER];
	int id;
};

struct class_distance{
	struct training_class tc;
	float distance;
	int id;
};

struct object{
	char *name;
	float e34[E34_MAX];
	float f0[F0_MAX];
	float gdf[GDF_MAX];
	float sa[SA_MAX];
};
