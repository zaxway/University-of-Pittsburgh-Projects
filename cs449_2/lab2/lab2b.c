#include <stdio.h>

int main() {

  printf("Please enter the weight you'd live to convert: \t ");
  char line[100];
  fgets(line, sizeof(line), stdin);
  int weight;
  sscanf(line, "%d", &weight);
  printf("Here are your weights for the other planets: \n");
  printf("\n");
  int mercury;
  mercury = weight * 0.38;
  int venus;
  venus = weight * 0.91;
  int mars;
  mars = weight * 0.38;
  int jupiter;
  jupiter = weight * 2.54;
  int saturn;
  saturn = weight * 1.08;
  int uranus;
  uranus = weight * 0.91;
  int neptune;
  neptune = weight * 1.19;
  printf("Mercury\t%d lbs \n", mercury);
  printf("Venus\t%d lbs \n", venus);
  printf("Mars\t%d lbs \n", mars);
  printf("Jupiter\t%d lbs \n", jupiter);
  printf("Saturn\t%d lbs \n", saturn);
  printf("Uranus\t%d lbs \n", uranus);
  printf("Neptune\t%d lbs \n", neptune);
  return 0;


}
