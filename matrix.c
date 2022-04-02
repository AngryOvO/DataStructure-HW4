// �������
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
// �Լ� ������Ÿ�� ����
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main() // �����Լ� ����
{

    char command; 
    printf("[----- [���Ͽ�]  [2018038025] -----]\n");

    int row, col; // �� �� ���� ���� ����
    srand(time(NULL)); // �����Լ��� �õ带 �ʱ�ȭ

    printf("Input row and col : "); 
    scanf("%d %d", &row, &col); //�� �� �Է�
    int** matrix_a = create_matrix(row, col); // ��� a
    int** matrix_b = create_matrix(row, col); // ��� b
    int** matrix_a_t = create_matrix(col, row); // a�� ��ġ��� 
   
    printf("Matrix Created.\n"); 

    //��� ������ �߸��Ǿ��� ��� ��ó��
    if (matrix_a == NULL || matrix_b == NULL) {return -1;}

    do{ // �޴� 
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command); // �޴� ���ÿ� ĳ������ ����

        switch(command) { // �޴� �Է� ���ǹ�
        case 'z': case 'Z':
            printf("Matrix Initialized\n"); 
            fill_data(matrix_a, row, col); // ��� a�� b�� ���� ����
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':
            printf("Print matrix\n"); // ��� a�� b ���
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n"); //��� a�� b�� ���� �� ���
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n"); // ��� a �� b�� ���� ���
            subtraction_matrix(matrix_a, matrix_b, row, col); 
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n"); //��� a �� ��ġ��� a_t ����
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            printf("matrix_a\n");
            print_matrix(matrix_a,row,col);
            printf("matrix_a_t\n");
            print_matrix(matrix_a_t, col, row); //��ġ��� a_t���
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n"); // ���a�� ��ġ��� t�� ���ϰ� ���
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q': // ����
            printf("Free all matrices..\n"); //�����Ҵ�� �� ��ĵ��� �Ҵ� ���� �� ����
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //�߸��� �޴� ���ý�
            break;
        }

    }while(command != 'q' && command != 'Q'); // q�� Q�� ���ý� ���� ����

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col) // ��� ���� �Լ�
{
    if (row <= 0 || col <= 0) // ������ �Է½� ��� ����
    {
        printf("��� ���� ũ�Ⱑ �߸��Ǿ����ϴ�.\n");
        return NULL;
    }
    
     
    //���������� ���� x�� ����� ���ÿ� �����Ҵ�
   int **x = (int**)calloc(row,sizeof(int*)); // x�� �� �迭�� �ּҸ� ���� ������ ������ x ���� ������ �����Ҵ�� ���ÿ� 0���� �ʱ�ȭ

    for(int i = 0; i < row; i++) // �ุŭ �ݺ�
    {
        x[i] = (int*)calloc(col,sizeof(int)); // ���� �迭�� ���� ����� int ������ x ���� ������ �����Ҵ�� ���ÿ� 0���� �ʱ�ȭ
    }
    //�����Ҵ� ���н� ��� ����
    if(x == NULL)
    {
        printf("�޸� �����Ҵ��� �߸��Ǿ����ϴ�.\n");
        return NULL;
    }

    return x; // x ����
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col) // ��� ��� �Լ�
{
    if (row <= 0 || col <= 0) // ������ �Է½� ��� ����
    {
        printf("��� ���� ũ�Ⱑ �߸��Ǿ����ϴ�.\n");
    }
    
    for(int i=0; i< row; i++) // �� ��ŭ �ݺ�
    {
        for(int j =0; j < col; j++) //�� ��ŭ �ݺ�
        {
            printf("%d  ",matrix[i][j]); //����� �� ���
        }
        printf("\n\n");
    }
    //�����Ҵ� ���н� ��� ����
    if(matrix == NULL)
    {
        printf("�޸� �����Ҵ��� �߸��Ǿ����ϴ�.\n");
    }


}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col) // �����Ҵ� ����
{
    if (row <= 0 || col <= 0) // ������ �Է½� ��� ����
    {
        printf("��� ���� ũ�Ⱑ �߸��Ǿ����ϴ�.\n");
        return -1;
    }
    
    for(int i =0; i<row; i++) //�迭�� ���� ���� �� �κ� ����
    {
        free(matrix[i]);
    }

    free(matrix); //�迭�� �� ���� �ּҵ��� ������ �����Ҵ� ����
    //�����Ҵ��� �����ǹǷ� �����Ҵ翡 ���� ��ó�� �Լ��� �ʿ����.
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col) // ����� ���������� ä��� �Լ�
{
    if (row <= 0 || col <= 0) // ������ �Է½� ��� ����
    {
        printf("��� ���� ũ�Ⱑ �߸��Ǿ����ϴ�.\n");
        return -1;
    }

    for(int i = 0; i<row; i++) // �ุŭ �ݺ� 
    {
        for(int j = 0; j < col; j++) // ����ŭ �ݺ�
        {
            matrix[i][j] = rand()%20;  // �� ����� ������ 0 ~ 19 ������ ������ ä��
        }
    }

    //�����Ҵ� ���н� ��� ����
    if(matrix == NULL)
    {
        printf("�޸� �����Ҵ��� �߸��Ǿ����ϴ�.\n");
        return -1;
    }
    return 1;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col) // ����� �� ��� �Լ�
{
    if (row <= 0 || col <= 0) // ������ �Է½� ��� ����
    {
        printf("��� ���� ũ�Ⱑ �߸��Ǿ����ϴ�.\n");
        return -1;
    }

    int **matrix_sum = create_matrix(row,col);

    for(int i=0; i<row; i++) // �ุŭ �ݺ�
    {
        for(int j=0; j<col; j++) // ����ŭ �ݺ�
        {
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j]; //�� ����� �� ������ ����
        }
        printf("\n\n");
    }
    if(matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL)
    {
        printf("�޸� �����Ҵ��� �߸��Ǿ����ϴ�.\n");
        return -1;
    }
    // matrix_sum ��� �� �Ҵ� ����
    print_matrix(matrix_sum,row,col);
    free_matrix(matrix_sum,row,col);
    return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col) // ����� �� ��� �Լ�
{
    if (row <= 0 || col <= 0) // ������ �Է½� ��� ����
    {
        printf("��� ���� ũ�Ⱑ �߸��Ǿ����ϴ�.\n");
        return -1;
    }

    int ** matrix_sub = create_matrix(row,col);

    for(int i=0; i<row; i++) // �ุŭ �ݺ�
    {
        for(int j=0; j<col; j++) // ����ŭ �ݺ�
        {
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j]; // �� ����� �� ������ ��
        }
        printf("\n\n");
    }
    if(matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL)
    {
        printf("�޸� �����Ҵ��� �߸��Ǿ����ϴ�.\n");
        return -1;
    }
    //matrix_sub ��� �� �Ҵ� ����
    print_matrix(matrix_sub,row,col);
    free_matrix(matrix_sub,row,col);
    return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) // ��ġ��� ���� �Լ�
{
    if (row <= 0 || col <= 0) // ������ �Է½� ��� ����
    {
        printf("��� ���� ũ�Ⱑ �߸��Ǿ����ϴ�.\n");
        return -1;
    }

    for(int i=0; i<row; i++) // �ุŭ �ݺ�
    {
        for(int j=0; j<col; j++) // ����ŭ �ݺ�
        {
            matrix_t[i][j] = matrix[j][i]; // ����� ��� ���� ��ü
        }

    }
    if(matrix == NULL || matrix_t == NULL)
    {
        printf("�޸� �����Ҵ��� �߸��Ǿ����ϴ�.\n");
        return -1;
    }
    
    return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col) // ��� �� ��� �Լ�
{
    if (row <= 0 || col <= 0) // ������ �Է½� ��� ����
    {
        printf("��� ���� ũ�Ⱑ �߸��Ǿ����ϴ�.\n");
        return -1;
    }
    int sum = 0; // �� ����� �� ������ �Է� �� ���� ���� , 0���� �ʱ�ȭ
    // ��ġ��İ��� ���̹Ƿ� ��İ��� ����( ���ϴ� ������� ���� �� ����� ���� ũ�Ⱑ ���ƾ� �Ѵ�)�� �����ߴ�.
    int** matrix_mul = create_matrix(row,row); // row * col  X  col * row �� ũ��� row * row

    for(int i=0; i < row; i++)  // ���� ����� �ุŭ �ݺ��ؾ��ϹǷ� row �� �ݺ�
    {
        for(int j=0; j < row; j++) // col�� �ݺ��Ǵ� �� ������ ���� ��ġ ����� ����ŭ �ݺ��ǹǷ� row�� �ݺ�
        {
            for(int k=0; k<col; k++)  // ���� ����� ���� ������ ��ġ����� ���� ������ col�� ���� ������ �� ������ ���� �� col��
            {
             //sum�� ���� �� ������ ������ ���� ���� ������ ���������� ���� sum�� ���� ����� ���� ���� ���� 
               sum += (matrix_a[i][k] * matrix_t[k][j]);
            }
            matrix_mul[i][j] = sum;
            sum = 0; // sum �ٽ� 0���� �ʱ�ȭ
        }
        printf("\n\n");
    }
    if(matrix_a == NULL || matrix_t == NULL || matrix_mul == NULL)
    {
        printf("�޸� �����Ҵ��� �߸��Ǿ����ϴ�.\n");
        return -1;
    }
    // matrix_mul ��� �� �Ҵ� ����
    print_matrix(matrix_mul,row,row);
    free_matrix(matrix_mul,row,row);
    return 1;
}
