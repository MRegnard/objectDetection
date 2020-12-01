
#include "header.h"


# define NB_OCCURRENCES_MAX 5000




void mean(int nbDimensions , float values[][nbDimensions] , int* classes , int considered_class , float res[nbDimensions]) {

	int n = 0 ;
	int i,j ;

	for(i = 0 ; i<nbDimensions ; i++)
		res[i] = 0.0 ;


	for(i = 0 ; i<PICTURES_NUMBER ; i++) {

		if(classes[i]==considered_class)  {

			n++ ;

			for(j = 0 ; j<nbDimensions ; j++) {
				res[j] += values[i][j] ;
			}

		}

	}



	for(i = 0 ; i<nbDimensions ; i++) {

		res[i] /= n ;

	}


}


void allmeans(int nbDimensions , float values[][nbDimensions] , int* classes, float means[][nbDimensions]) {
	for(int i = 1 ; i<=CLASS_NUMBER ; i++) {
		mean(nbDimensions,values,classes,i,means[i-1]) ;
	}
}



int nb_occurences(int classes[PICTURES_NUMBER], int considered_class) {
	int n = 0 ;
	for(int i=0 ; i<PICTURES_NUMBER ; i++) {
		if(classes[i] == considered_class) {
			n++ ;
		}
	}
	return n ;
}



int split_equally(int classes[PICTURES_NUMBER]) {
	int expected_size = PICTURES_NUMBER/CLASS_NUMBER ;

	// If this works from 1 to NB_CLASSES-1 , it will work too for NB_CLASSES
	for(int i = 1 ; i<CLASS_NUMBER ; i++) {
		if(nb_occurences(classes,i) != expected_size) {
			return 0 ;
		}
	}
	return 1 ;
}



float distance(float* pointA, float* pointB , int nbDimensions) {

	float res = 0.0 ;

	for(int i = 0 ; i<nbDimensions ; i++) {
		res += pow((pointA[i]-pointB[i]),2) ;
	}

	return res ;

}


int class(int nbDimensions,float value[nbDimensions], float means[][nbDimensions]) {
	int res = 1 ;
	float dist = distance(value,means[0],nbDimensions) ;
	float new_dist ;
	for(int i=1 ; i<CLASS_NUMBER ; i++) {
		new_dist = distance(value,means[i],nbDimensions) ;
		if(new_dist<dist) {
			dist = new_dist ;
			res = i+1 ;
		}
	}
	return res ;
}








void kmeans(int nbDimensions , float values[][nbDimensions] , int* classes , int permitted_occurences , int* res) {

	if((permitted_occurences==0) || split_equally(classes)) {

		for(int i = 0 ; i<PICTURES_NUMBER ; i++) {
			res[i] = classes[i] ;
		}

	}

	else {

		float means[CLASS_NUMBER][nbDimensions] ;

		allmeans(nbDimensions,values,classes,means) ;

		for(int i = 0 ; i<PICTURES_NUMBER ; i++) {
			classes[i] = class(nbDimensions,values[i],means) ;
		}

		kmeans(nbDimensions,values,classes,permitted_occurences-1,res) ;
	}
}





void cluster(struct object * objects , enum method method , int nbDimensions , int* res) {


	float values[PICTURES_NUMBER][nbDimensions] ;


	switch(method) {

	case E34 :
		for(int i = 0 ; i<PICTURES_NUMBER ; i++)  {
			for(int j = 0 ; j<nbDimensions ; j++) {
				values[i][j] = objects[i].e34[j] ;
			}
		}
		break ;


	case F0 :
		for(int i = 0 ; i<PICTURES_NUMBER ; i++)  {
			for(int j = 0 ; j<nbDimensions ; j++) {
				values[i][j] = objects[i].f0[j] ;
			}
		}
		break ;

	case GDF :
		for(int i = 0 ; i<PICTURES_NUMBER ; i++)  {
			for(int j = 0 ; j<nbDimensions ; j++) {
				values[i][j] = objects[i].gdf[j] ;
			}
		}
		break ;

	case SA :
		for(int i = 0 ; i<PICTURES_NUMBER ; i++)  {
			for(int j = 0 ; j<nbDimensions ; j++) {
				values[i][j] = objects[i].sa[j] ;
			}
		}
		break ;


	}


	int first_classes[PICTURES_NUMBER] ;

	for(int i = 0 ; i<CLASS_NUMBER ; i++) {
		first_classes[i] = i+1 ;
	}

	for(int i = CLASS_NUMBER ; i<PICTURES_NUMBER ; i++) {
		first_classes[i] = 0 ;
	}


	for(int i = 0 ; i<PICTURES_NUMBER ; i++) {
		res[i] = first_classes[i] ;
	}

	kmeans(nbDimensions,values,first_classes,NB_OCCURRENCES_MAX,res) ;


}



int clustering(struct object * objects , enum method method , int* res) {

	int nbDimensions ;

	switch(method) {
	case E34: nbDimensions = E34_MAX ; break ;
	case F0 : nbDimensions = F0_MAX ; break ;
	case GDF : nbDimensions = GDF_MAX ; break ;
	case SA : nbDimensions = SA_MAX ; break ;
	default : return EXIT_FAILURE ;
	}

	cluster(objects,method,nbDimensions,res) ;

	return EXIT_SUCCESS ;
}




