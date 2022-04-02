// 헤더파일
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
// 함수 프로토타입 선언
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main() // 메인함수 시작
{

    char command; 
    printf("[----- [정하용]  [2018038025] -----]\n");

    int row, col; // 행 열 받을 변수 선언
    srand(time(NULL)); // 랜덤함수의 시드를 초기화

    printf("Input row and col : "); 
    scanf("%d %d", &row, &col); //행 열 입력
    int** matrix_a = create_matrix(row, col); // 행렬 a
    int** matrix_b = create_matrix(row, col); // 행렬 b
    int** matrix_a_t = create_matrix(col, row); // a의 전치행렬 
   
    printf("Matrix Created.\n"); 

    //행렬 생성이 잘못되었을 경우 후처리
    if (matrix_a == NULL || matrix_b == NULL) {return -1;}

    do{ // 메뉴 
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command); // 메뉴 선택용 캐릭터형 변수

        switch(command) { // 메뉴 입력 조건문
        case 'z': case 'Z':
            printf("Matrix Initialized\n"); 
            fill_data(matrix_a, row, col); // 행렬 a와 b에 난수 생성
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':
            printf("Print matrix\n"); // 행렬 a와 b 출력
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n"); //행렬 a와 b를 더한 값 출력
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n"); // 행렬 a 와 b를 뺀값 출력
            subtraction_matrix(matrix_a, matrix_b, row, col); 
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n"); //행렬 a 의 전치행렬 a_t 생성
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            printf("matrix_a\n");
            print_matrix(matrix_a,row,col);
            printf("matrix_a_t\n");
            print_matrix(matrix_a_t, col, row); //전치행렬 a_t출력
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n"); // 행렬a와 전치행렬 t를 곱하고 출력
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q': // 종료
            printf("Free all matrices..\n"); //동적할당된 각 행렬들을 할당 해제 후 종료
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //잘못된 메뉴 선택시
            break;
        }

    }while(command != 'q' && command != 'Q'); // q나 Q를 선택시 루프 해제

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col) // 행렬 생성 함수
{
    if (row <= 0 || col <= 0) // 비정상 입력시 경고문 생성
    {
        printf("행과 열의 크기가 잘못되었습니다.\n");
        return NULL;
    }
    
     
    //이중포인터 변수 x를 선언과 동시에 동적할당
   int **x = (int**)calloc(row,sizeof(int*)); // x에 각 배열의 주소를 받을 포인터 사이즈 x 행의 공간을 동적할당과 동시에 0으로 초기화

    for(int i = 0; i < row; i++) // 행만큼 반복
    {
        x[i] = (int*)calloc(col,sizeof(int)); // 실제 배열의 값이 저장될 int 사이즈 x 열의 공간을 동적할당과 동시에 0으로 초기화
    }
    //동적할당 실패시 경고문 생성
    if(x == NULL)
    {
        printf("메모리 동적할당이 잘못되었습니다.\n");
        return NULL;
    }

    return x; // x 리턴
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col) // 행렬 출력 함수
{
    if (row <= 0 || col <= 0) // 비정상 입력시 경고문 생성
    {
        printf("행과 열의 크기가 잘못되었습니다.\n");
    }
    
    for(int i=0; i< row; i++) // 행 만큼 반복
    {
        for(int j =0; j < col; j++) //열 만큼 반복
        {
            printf("%d  ",matrix[i][j]); //행렬의 값 출력
        }
        printf("\n\n");
    }
    //동적할당 실패시 경고문 생성
    if(matrix == NULL)
    {
        printf("메모리 동적할당이 잘못되었습니다.\n");
    }


}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col) // 동적할당 해제
{
    if (row <= 0 || col <= 0) // 비정상 입력시 경고문 생성
    {
        printf("행과 열의 크기가 잘못되었습니다.\n");
        return -1;
    }
    
    for(int i =0; i<row; i++) //배열의 실제 값이 들어간 부분 해제
    {
        free(matrix[i]);
    }

    free(matrix); //배열의 각 행의 주소들을 저장한 동적할당 해제
    //동적할당이 해제되므로 동적할당에 대한 후처리 함수는 필요없다.
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col) // 행렬을 랜덤값으로 채우는 함수
{
    if (row <= 0 || col <= 0) // 비정상 입력시 경고문 생성
    {
        printf("행과 열의 크기가 잘못되었습니다.\n");
        return -1;
    }

    for(int i = 0; i<row; i++) // 행만큼 반복 
    {
        for(int j = 0; j < col; j++) // 열만큼 반복
        {
            matrix[i][j] = rand()%20;  // 각 행렬의 성분을 0 ~ 19 사이의 값으로 채움
        }
    }

    //동적할당 실패시 경고문 생성
    if(matrix == NULL)
    {
        printf("메모리 동적할당이 잘못되었습니다.\n");
        return -1;
    }
    return 1;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col) // 행렬의 합 출력 함수
{
    if (row <= 0 || col <= 0) // 비정상 입력시 경고문 생성
    {
        printf("행과 열의 크기가 잘못되었습니다.\n");
        return -1;
    }

    int **matrix_sum = create_matrix(row,col);

    for(int i=0; i<row; i++) // 행만큼 반복
    {
        for(int j=0; j<col; j++) // 열만큼 반복
        {
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j]; //두 행렬의 각 성분을 더함
        }
        printf("\n\n");
    }
    if(matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL)
    {
        printf("메모리 동적할당이 잘못되었습니다.\n");
        return -1;
    }
    // matrix_sum 출력 및 할당 해제
    print_matrix(matrix_sum,row,col);
    free_matrix(matrix_sum,row,col);
    return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col) // 행렬의 차 출력 함수
{
    if (row <= 0 || col <= 0) // 비정상 입력시 경고문 생성
    {
        printf("행과 열의 크기가 잘못되었습니다.\n");
        return -1;
    }

    int ** matrix_sub = create_matrix(row,col);

    for(int i=0; i<row; i++) // 행만큼 반복
    {
        for(int j=0; j<col; j++) // 열만큼 반복
        {
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j]; // 두 행렬의 각 성분을 뺌
        }
        printf("\n\n");
    }
    if(matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL)
    {
        printf("메모리 동적할당이 잘못되었습니다.\n");
        return -1;
    }
    //matrix_sub 출력 및 할당 해제
    print_matrix(matrix_sub,row,col);
    free_matrix(matrix_sub,row,col);
    return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) // 전치행렬 생성 함수
{
    if (row <= 0 || col <= 0) // 비정상 입력시 경고문 생성
    {
        printf("행과 열의 크기가 잘못되었습니다.\n");
        return -1;
    }

    for(int i=0; i<row; i++) // 행만큼 반복
    {
        for(int j=0; j<col; j++) // 열만큼 반복
        {
            matrix_t[i][j] = matrix[j][i]; // 행렬의 행과 열을 교체
        }

    }
    if(matrix == NULL || matrix_t == NULL)
    {
        printf("메모리 동적할당이 잘못되었습니다.\n");
        return -1;
    }
    
    return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col) // 행렬 곱 출력 함수
{
    if (row <= 0 || col <= 0) // 비정상 입력시 경고문 생성
    {
        printf("행과 열의 크기가 잘못되었습니다.\n");
        return -1;
    }
    int sum = 0; // 두 행렬의 각 성분을 입력 할 변수 생성 , 0으로 초기화
    // 정치행렬과의 곱이므로 행렬곱의 조건( 곱하는 앞행렬의 열과 뒤 행렬의 행의 크기가 같아야 한다)은 제외했다.
    int** matrix_mul = create_matrix(row,row); // row * col  X  col * row 의 크기는 row * row

    for(int i=0; i < row; i++)  // 기존 행렬의 행만큼 반복해야하므로 row 번 반복
    {
        for(int j=0; j < row; j++) // col번 반복되는 각 성분의 곱이 전치 행렬의 열만큼 반복되므로 row번 반복
        {
            for(int k=0; k<col; k++)  // 기존 행렬의 열의 개수와 전치행렬의 행의 개수가 col로 같기 때문에 각 성분의 곱은 총 col번
            {
             //sum의 값에 각 성분의 곱들의 합을 저장 루프를 빠져나갔을 때의 sum의 값이 행렬을 곱한 값의 성분 
               sum += (matrix_a[i][k] * matrix_t[k][j]);
            }
            matrix_mul[i][j] = sum;
            sum = 0; // sum 다시 0으로 초기화
        }
        printf("\n\n");
    }
    if(matrix_a == NULL || matrix_t == NULL || matrix_mul == NULL)
    {
        printf("메모리 동적할당이 잘못되었습니다.\n");
        return -1;
    }
    // matrix_mul 출력 및 할당 해제
    print_matrix(matrix_mul,row,row);
    free_matrix(matrix_mul,row,row);
    return 1;
}
