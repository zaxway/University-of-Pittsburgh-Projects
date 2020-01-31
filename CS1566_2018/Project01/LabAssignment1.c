//#include <stdio.h>

void matrixOfMinor(float arr[][4], float arr2[][4]);
void subtractMatrix(float arr[][4], float arr2[][4], float arr3[][4]);
void addMatrix(float arr[][4], float arr2[][4], float arr3[][4]);
void transposeMatrix(float arr[][4], float arr2[][4]);
void multiplyByScalar(float arr[][4], float d, float arr2[][4]);
void multiplyMatrix(float arr[][4], float arr2[][4], float arr3[][4]);
void printMatrix(float arr[][4]);
void getMatrix(float arr[][4]);
void printVector(float vec[4]);
void getVector(float vec[4]);
void addVector(float vec[4], float vec2[4], float dest[4]);
void subtractVector(float vec[4], float vec2[4], float dest[4]);
void multiplyVector(float vec[4], float vec2[4], float dest[4]);
void multiplyByScalarVecs(float vec[4], float dest[4]);
void cofactor(float arr[][4]);
float determinant(float arr[][4], float arr2[][4]);
void inverseMatrix(float arr[][4], float arr2[][4], float d);
float dotProduct(float vec[4], float vec2[4]);
void printCrossVector(float vec[4]);
void getCrossVector(float vec[3]);
void crossProduct(float vec[3], float vec2[3], float dest[3]);




//int main() {
//    float array1[4][4], array2[4][4], array3[4][4], array4[4][4], array5[4][4];
//    static float array[4][4];
//    float k = 4;
//    float determ;
//
////    printf("Enter Matrix1\n");
////    getMatrix(array1);
////    printMatrix(array1);
////    // second array has been intialized
////    printf("Enter Matrix2\n");
////    getMatrix(array2);
////    printMatrix(array2);
//
//    //printf("This is the matrix's addition: Matrix1 + Matrix2 \n");
//    addMatrix(array1, array2, array3);
//    printMatrix(array3);
//
//    //printf("This is the matrix's subtraction: Matrix1 - Matrix2 \n");
//    subtractMatrix(array1, array2, array3);
//    printMatrix(array3);
//
//    //printf("This is the matrix's multiplcation: Matrix1 * Matrix2 \n");
//    multiplyMatrix(array1, array2, array3);
//    printMatrix(array3);
//
//    //printf("Let's multiple our result matrix by a scalar (5) too: Matrix3 * 5 \n");
//    multiplyByScalar(array3, array4);
//    printMatrix(array4);
//
//    printf("This is transpose of matrix1 \n");
//    transposeMatrix(array1, array3);
//    printMatrix(array3);
//
//    printf("This is the inverse of matrix1 \n");
//    matrixOfMinor(array1, array3);
//    // printf("This is the matrix of minor \n");
//    // printMatrix(array3); // matrix of Minor is in array3
//    cofactor(array3);
//    // printf("This is its cofactor \n");
//    // printMatrix(array3);
//    transposeMatrix(array3, array4); // transpose matrix of minor cofactored stored in array4
//    determ = determinant(array1, array3); // determinant stored in determ
//    inverseMatrix(array4, array5, determ); // inverse stored in array5
//    printMatrix(array5);
//
//
//
//    // Vector Part
//    float vec[4],vec2[4], dest[4];
//    float v[3], v2[3], d[3]; // specifically for cross products
//    float dot;
//
//    printf("Enter first vector \n");
//    getVector(vec);
//    printVector(vec);
//
//    printf("Enter second vector \n");
//    getVector(vec2);
//    printVector(vec2);
//
//    printf("Let's add the vectors \n");
//    addVector(vec, vec2, dest);
//    printVector(dest);
//
//    printf("Let's subtract the vectors \n");
//    subtractVector(vec, vec2, dest);
//    printVector(dest);
//
//    printf("Let's multiply the vectors \n");
//    multiplyVector(vec, vec2, dest);
//    printVector(dest);
//
//    printf("Now let's multiply the first vector by 5, a scalar \n");
//    multiplyByScalarVecs(vec, dest);
//    printVector(dest);
//
//    printf("Let's do the dot product of our vectors \n");
//    dot = dotProduct(vec, vec2);
//    printf("%f", dot);
//    printf("\n");
//
//    printf("Enter 3 by 1 Vector \n");
//    getCrossVector(v);
//    printCrossVector(v);
//    printf("Enter the next 3 by 1 Vector \n");
//    getCrossVector(v2);
//    printCrossVector(v2);
//    printf("Let's do the cross product of our vectors \n");
//    crossProduct(v, v2, d);
//    printCrossVector(d);
//
//    return 0;
//
//
//}

void crossProduct(float vec[3], float vec2[3], float dest[3]) {
  dest[0] = ((vec[1] * vec2[2]) - (vec[2] * vec2[1]));
  dest[1] = ((vec[2] * vec2[0]) - (vec[0] * vec2[2]));
  dest[2] = ((vec[0] * vec2[1]) - (vec[1] * vec2[0]));

}
void printCrossVector(float vec[3]) {
  int i;
  //printf("The vector is: \n");
  for (i = 0; i < 3; ++i) {
   // printf(" %f", vec[i]);
   // printf("\n");
  }
}

void getCrossVector(float vec[3]) {
  int i;
  for (i = 0; i < 3; ++i)
  {
    //scanf("%f", &vec[i]);
  }
}

float dotProduct(float vec[4], float vec2[4]) {
  float result = 0;
  int i;
  for(i = 0; i < 4; i++) {
    result += vec[i]*vec2[i];
  }
  return result;
}

void multiplyByScalarVecs(float vec[4], float dest[4]) {
  int i;
  for(i = 0; i < 4; ++i) {
    dest[i] = vec[i] * 5;
  }
}
void multiplyVector(float vec[4], float vec2[4], float dest[4]) {
  int i;
  for(i = 0; i < 4; ++i) {
    dest[i] = vec[i] * vec2[i];
  }
}

void subtractVector(float vec[4], float vec2[4], float dest[4]) {
  int i;
  for(i = 0; i < 4; ++i) {
    dest[i] = vec[i] - vec2[i];
  }
}
void addVector(float vec[4], float vec2[4], float dest[4]) {
  int i;
  for(i = 0; i < 4; ++i) {
    dest[i] = vec[i] + vec2[i];
  }
}
void getVector(float vec[4]) {
  int i;
  for (i = 0; i < 4; ++i)
  {
   // scanf("%f", &vec[i]);
  }
}

void printVector(float vec[4]) {
  int i;
  //printf("The vector is: \n");
  for (i = 0; i < 4; ++i) {
    //printf(" %f", vec[i]);
    //printf("\n");
  }
}

void getMatrix(float arr[][4]) {
  int i, j;
  for (i = 0; i < 4; ++i)
  {
      for (j = 0; j < 4; ++j)
      {
        //  scanf("%f", &arr[i][j]);
      }
  }
}

void printMatrix(float arr[][4]) {
  int i,j;
  //printf("The matrix is:  \n");
  for (i = 0; i < 4; ++i)
  {
      for (j = 0; j < 4; ++j)
      {
          //printf(" %f", arr[i][j]);
      }
      //printf("\n");
  }
}

void multiplyMatrix(float arr[][4], float arr2[][4], float arr3[][4]) {
  int i, j, k;
  for(i = 0; i < 4; i++) {
    for(j = 0; j < 4; j++) {
      arr3[i][j] = 0;
      for(k = 0; k < 4; k++) {
        arr3[i][j] = arr3[i][j] + arr[i][k] * arr2[k][j];
      }
    }
  }
}

void multiplyByScalar(float arr[][4], float d, float arr2[][4]) {
  int i, j;
  for(j = 0; j < 4; ++j) {
    for(i = 0; i < 4; ++i) {
      arr2[i][j] = arr[i][j] * d;
    }
  }
}

void transposeMatrix(float arr[][4], float arr2[][4]) {
  int i, j;
  for (i = 0; i < 4; ++i) {
    for(j = 0; j < 4; ++j) {
      arr2[i][j] = arr[j][i];
    }
  }
}

void addMatrix(float arr[][4], float arr2[][4], float arr3[][4]) {
  int i, j;
  for(j = 0; j < 4; ++j) {
    for(i = 0; i < 4; ++i) {
      arr3[i][j] = arr[i][j] + arr2[i][j];
    }
  }
}

void subtractMatrix(float arr[][4], float arr2[][4], float arr3[][4]) {
  int i, j;
  for(j = 0; j < 4; ++j) {
    for(i = 0; i < 4; ++i) {
      arr3[i][j] = arr[i][j] - arr2[i][j];
    }
  }
}

void matrixOfMinor(float arr[][4], float arr2[][4]) {
  arr2[0][0] = (arr[1][1] * arr[2][2] * arr[3][3]) + (arr[1][2] * arr[2][3] * arr[3][1]) + (arr[1][3] * arr[2][1] * arr[3][2])
              - (arr[3][1] * arr[2][2] * arr[1][3]) - (arr[3][2] * arr[2][3] * arr[1][1]) - (arr[3][3] * arr[2][1] * arr[1][2]);

  arr2[0][1] = (arr[1][0] * arr[2][2] * arr[3][3]) + (arr[1][2] * arr[2][3] * arr[3][0]) + (arr[1][3] * arr[2][0] * arr[3][2])
              - (arr[3][0] * arr[2][2] * arr[1][3]) - (arr[3][2] * arr[2][3] * arr[1][0]) - (arr[3][3] * arr[2][0] * arr[1][2]);

  arr2[0][2] = (arr[1][0] * arr[2][1] * arr[3][3]) + (arr[1][1] * arr[2][3] * arr[3][0]) + (arr[1][3] * arr[2][0] * arr[3][1])
              - (arr[3][0] * arr[2][1] * arr[1][3]) - (arr[3][1] * arr[2][3] * arr[1][0]) - (arr[3][3] * arr[2][0] * arr[1][1]);

  arr2[0][3] = (arr[1][0] * arr[2][1] * arr[3][2]) + (arr[1][1] * arr[2][2] * arr[3][0]) + (arr[1][2] * arr[2][0] * arr[3][1])
              - (arr[3][0] * arr[2][1] * arr[1][2]) - (arr[3][1] * arr[2][2] * arr[1][0]) - (arr[3][2] * arr[2][0] * arr[1][1]);

  arr2[1][0] = (arr[0][1] * arr[2][2] * arr[3][3]) + (arr[0][2] * arr[2][3] * arr[3][1]) + (arr[0][3] * arr[2][1] * arr[3][2])
              - (arr[3][1] * arr[2][2] * arr[0][3]) - (arr[3][2] * arr[2][3] * arr[0][1]) - (arr[3][3] * arr[2][1] * arr[0][2]);

  arr2[1][1] = (arr[0][0] * arr[2][2] * arr[3][3]) + (arr[0][2] * arr[2][3] * arr[3][0]) + (arr[0][3] * arr[2][0] * arr[3][2])
              - (arr[3][0] * arr[2][2] * arr[0][3]) - (arr[3][2] * arr[2][3] * arr[0][0]) - (arr[3][3] * arr[2][0] * arr[0][2]);

  arr2[1][2] = (arr[0][0] * arr[2][1] * arr[3][3]) + (arr[0][1] * arr[2][3] * arr[3][0]) + (arr[0][3] * arr[2][0] * arr[3][1])
              - (arr[3][0] * arr[2][1] * arr[0][3]) - (arr[3][1] * arr[2][3] * arr[0][0]) - (arr[3][3] * arr[2][0] * arr[0][1]);

  arr2[1][3] = (arr[0][0] * arr[2][1] * arr[3][2]) + (arr[0][1] * arr[2][2] * arr[3][0]) + (arr[0][2] * arr[2][0] * arr[3][1])
              - (arr[3][0] * arr[2][1] * arr[0][2]) - (arr[3][1] * arr[2][2] * arr[0][0]) - (arr[3][2] * arr[2][0] * arr[0][1]);

  arr2[2][0] = (arr[0][1] * arr[1][2] * arr[3][3]) + (arr[0][2] * arr[1][3] * arr[3][1]) + (arr[0][3] * arr[1][1] * arr[3][2])
              - (arr[3][1] * arr[1][2] * arr[0][3]) - (arr[3][2] * arr[1][3] * arr[0][1]) - (arr[3][3] * arr[1][1] * arr[0][2]);

  arr2[2][1] = (arr[0][0] * arr[1][2] * arr[3][3]) + (arr[0][2] * arr[1][3] * arr[3][0]) + (arr[0][3] * arr[1][0] * arr[3][2])
              - (arr[3][0] * arr[1][2] * arr[0][3]) - (arr[3][2] * arr[1][3] * arr[0][0]) - (arr[3][3] * arr[1][0] * arr[0][2]);

  arr2[2][2] = (arr[0][0] * arr[1][1] * arr[3][3]) + (arr[0][1] * arr[1][3] * arr[3][0]) + (arr[0][3] * arr[1][0] * arr[3][1])
              - (arr[3][0] * arr[1][1] * arr[0][3]) - (arr[3][1] * arr[1][3] * arr[0][0]) - (arr[3][3] * arr[1][0] * arr[0][1]);

  arr2[2][3] = (arr[0][0] * arr[1][1] * arr[3][2]) + (arr[0][1] * arr[1][2] * arr[3][0]) + (arr[0][2] * arr[1][0] * arr[3][1])
              - (arr[3][0] * arr[1][1] * arr[0][2]) - (arr[3][1] * arr[1][2] * arr[0][0]) - (arr[3][2] * arr[1][0] * arr[0][1]);

  arr2[3][0] = (arr[0][1] * arr[1][2] * arr[2][3]) + (arr[0][2] * arr[1][3] * arr[2][1]) + (arr[0][3] * arr[1][1] * arr[2][2])
              - (arr[2][1] * arr[1][2] * arr[0][3]) - (arr[2][2] * arr[1][3] * arr[0][1]) - (arr[2][3] * arr[1][1] * arr[0][2]);

  arr2[3][1] = (arr[0][0] * arr[1][2] * arr[2][3]) + (arr[0][2] * arr[1][3] * arr[2][0]) + (arr[0][3] * arr[1][0] * arr[2][2])
              - (arr[2][0] * arr[1][2] * arr[0][3]) - (arr[2][2] * arr[1][3] * arr[0][0]) - (arr[2][3] * arr[1][0] * arr[0][2]);

  arr2[3][2] = (arr[0][0] * arr[1][1] * arr[2][3]) + (arr[0][1] * arr[1][3] * arr[2][0]) + (arr[0][3] * arr[1][0] * arr[2][1])
              - (arr[2][0] * arr[1][1] * arr[0][3]) - (arr[2][1] * arr[1][3] * arr[0][0]) - (arr[2][3] * arr[1][0] * arr[0][1]);

  arr2[3][3] = (arr[0][0] * arr[1][1] * arr[2][2]) + (arr[0][1] * arr[1][2] * arr[2][0]) + (arr[0][2] * arr[1][0] * arr[2][1])
              - (arr[2][0] * arr[1][1] * arr[0][2]) - (arr[2][1] * arr[1][2] * arr[0][0]) - (arr[2][2] * arr[1][0] * arr[0][1]);

}

void cofactor(float arr[][4]) {
  arr[0][1] = (-1) * arr[0][1];
  arr[0][3] = (-1) * arr[0][3];

  arr[1][0] = (-1) * arr[1][0];
  arr[1][2] = (-1) * arr[1][2];

  arr[2][1] = (-1) * arr[2][1];
  arr[2][3] = (-1) * arr[2][3];

  arr[3][0] = (-1) * arr[3][0];
  arr[3][2] = (-1) * arr[3][2];

}

float determinant(float arr[][4], float arr2[][4]) {
  return ((arr[0][0] * arr2[0][0]) - (arr[0][1] * arr2[0][1]) + (arr[0][2] * arr2[0][2]) - (arr[0][3] * arr2[0][3]));
}

void inverseMatrix(float arr[][4], float arr2[][4], float d) {
  float scalar = (1 / d);
  int i, j;
  for(j = 0; j < 4; ++j) {
    for(i = 0; i < 4; ++i) {
      arr2[i][j] = arr[i][j] * scalar;
    }
  }
}
