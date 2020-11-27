# include "header.h"

# define NB_CLASSES 9
# define NB_OCCURRENCES_MAX 20
# define NB_PICTURES 99


float mean(float* values , int* classes , int considered_class) {
	float sum = 0.0 ;
	int n = 0 ;
	for(int i = 0 ; i<NB_PICTURES ; i++) {
		if(classes[i] = considered_class) {
			n++ ;
			sum += values[i] ;
		}
	}
	return sum/n ;
}



float* allmeans(float* values , int* classes) {
	float res[NB_CLASSES] ;
	for(int i = 1 ; i<NB_CLASSES ; i++) {
		res[i-1] = mean(values,classes,i) ;
	}
	return res ;
}






int nb_occurences(int* classes, int considered_class) {
	int n = 0 ;
	for(int i=0 ; i<NB_PICTURES ; i++) {
		if(classes[i] == considered_class) {
			n++ ;
		}
	}
}



int split_equally(int* classes) {
	int expected_size = NB_PICTURES/NB_CLASSES ;

	// If this works from 1 to NB_CLASSES-1 , it will work too for NB_CLASSES
	for(int i = 1 ; i<NB_CLASSES ; i++) {
		if(nb_occurences(classes,i) != expected_size) {
			return 0 ;
		}
	}
	return 1 ;
}





int class(float value, float* means) {
	int res = 1 ;
	float distance = fabs(value-means[0]) ;
	float new_distance ;
	for(i=1 ; i<NB_CLASSES ; i++) {
		new_distances = fabs(value-means[i]) ;
		if(new_distance<distance) {
			distance = new_distance ;
			res = i+1 ;
		}
	}
	return res ;
}







int* kmeans(float* values , int* classes , int permitted_occurences) {
	if(permitted_occurences==0 || split_equally(classes)) {
		return classes ;
	}

	float * means = allmeans(values,classes) ;

	for(int i = 0 ; i<NB_PICTURES ; i++) {
		classes[i] = class(values[i],means) ;
	}

	return kmeans(values,classes,permitted_occurences-1) ;
}





int* clustering(float* values) {
	int first_classes[NB_PICTURES] ;
	
	first_classes[0] = 0 ;

	for(int i = 1 ; i<=NB_CLASSES ; i++) {
		first_classes[i] = i ;
	}

	for(int i = NB_CLASSES+1 ; i<NB_PICTURES ; i++) {
		first_classes[i] = 0 ;
	}

	
	return kmeans(values,first_classes,NB_OCCURRENCES_MAX) ;
}

