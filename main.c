#include<stdio.h>
#include<math.h>

double A[10][10], vector[10], z[10], B[100][1000], e[10], eps, eMax, zMax = 1;
int step = 1, n, Case;
// Normalization of vector
void normal()
{
    zMax = fabs(z[0]);
    for(int i = 1; i < n; i++)
    {
        if(fabs(z[i]) > zMax)
            zMax = fabs(z[i]);
    }
    for(int i = 0; i < n; i++)
    {
        z[i] =(z[i] / zMax);
    }
}
// Multiplication of matrix and vector
void multi(int m)
{
    for(int i = 0; i < n; i++)
    {
        z[i] = 0;
        for(int j = 0; j < n; j++)
        {
            z[i] = z[i] + A[i][j] * B[m][j];
        }
    }
    normal();
    for(int i = 0; i < n; i++)
    {
        B[m + 1][i] = z[i];
    }
}

double check(int h, int k)
{
    for(int i = 0; i < n; i++)
    {
        e[i] = 0;
        e[i] = B[h][i] - B[k][i];
    }
    eMax = fabs(e[0]);
    for(int i = 1; i < n; i++)
    {
        if(fabs(e[i]) > eMax)
            eMax = fabs(e[i]);
    }
    return eMax;
}
// power method
void power()
{
    for(int i = 0; i < n; i++)
    {
        B[0][i] = vector[i];
    }
    multi(0);
    multi(1);
    multi(2);
    step = 3;
    Case = 4;
    while(1)
    {
        if(step == 100) break;
        if(check(step, step - 1  ) <= eps)
        {
            Case = 1;
            break;
        }
        if(check(step, step - 2) <= eps)
        {
            Case = 3;
            break;
        }
        step++;
        multi(step - 1);
        // printf("\nStep is: %d\n", step);
        // for(int i = 0; i < n; i++)
        // {
        //     printf("%lf\t", B[step][i]);
        // }
        // printf("\n");
    }
}
double max(double C[1][10])
{
    double max = fabs(C[0][0]);
    for(int i = 0; i < n; i++)
    {
        if(fabs(C[0][i]) > max)
            max = fabs(C[0][i]);
    }
    return max;
}
int main()
{
    // input matrix
    printf("\nEnter the order of matrix:");
    scanf("%d", &n);
    printf("\nEnter matrix:\n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            scanf("%lf", &A[i][j]);
        }
    }
    // input vector
    printf("\nEnter the vector\n");
    for(int i = 0; i < n; i++)
    {
        scanf("%lf", &vector[i]);
    }
    // input epsilon
    printf("Enter epsilon value\n");
    scanf("%lf", &eps);
    // calculation
    power();
    printf("Case is: %d\n", Case);
    if(Case == 1)
    {
        printf("Number of steps is: %d\n", step);
        double eVector[1][10];
        for(int i = 0; i < n; i++)
        {
            eVector[0][i] = B[step][i];
        }
        printf("\nThe eigenvector is:\n");
        for(int i = 0; i < n; i++)
        {
            printf("%.15lf\n", eVector[0][i]);
        }
        printf("\n");
        double AV[1][10], transpose_eVector[10][1], V_TAV[10][1], V_TV[1][1];
        for(int i = 0; i < n; i++)
        {
            AV[0][i] = 0;
            for(int j = 0; j < n; j++)
            {
                AV[0][i] = AV[0][i] + A[i][j] * eVector[0][j];
            }
        }
        for(int i = 0; i < n; i++)
        {
            transpose_eVector[i][0] = eVector[0][i];
        }
        for(int i = 0; i < n; i++)
        {
            V_TAV[i][0] = 0;
            for(int j = 0; j < n; j++)
            {
                V_TAV[i][0] = V_TAV[i][0] + transpose_eVector[j][0] * AV[0][j];
            }
        }
        for(int i = 0; i < n; i++)
        {
            V_TV[0][0] = V_TV[0][0] + transpose_eVector[i][0] * eVector[0][i];
        }
        printf("The eigenvalue is: %.15lf\n", V_TAV[0][0] / V_TV[0][0]);
    }
    if(Case == 3)
    {
        printf("Number of steps is: %d\n", step);
        double V[1][10], AV[1][10], A1V[1][10], A2V[1][10];
        for(int i = 0; i < n; i++)
        {
            V[0][i] = B[step][i];
        }
        for(int i = 0; i < n; i++)
        {
            AV[0][i] = 0;
            for(int j = 0; j < n; j++)
            {
                AV[0][i] = AV[0][i] + A[i][j] * V[0][j];
            }
        }
        for(int i = 0; i < n; i++)
        {
            A1V[0][i] = 0;
            for(int j = 0; j < n; j++)
            {
                A1V[0][i] = A1V[0][i] + A[i][j] * AV[0][j];
            }
        }
        for(int i = 0; i < n; i++)
        {
            A2V[0][i] = 0;
            for(int j = 0; j < n; j++)
            {
                A2V[0][i] = A2V[0][i] + A[j][i] * A1V[0][j];
            }
        }
        printf("\n");
        double eValue = sqrt((max(A2V) /  max(AV)));
        printf("The eigenvalues are: %.15lf\t%.15lf\n", eValue, -eValue);
        double eVector1[1][10], eVector2[1][10];
        for(int i = 0; i < n; i++)
        {
            eVector1[0][i] = A1V[0][i] + eValue * AV[0][i];
        }
        for(int i = 0; i < n; i++)
        {
            eVector2[0][i] = A1V[0][i] - eValue * AV[0][i];
        }
        double maxE1 = max(eVector1);
        double maxE2 = max(eVector2);
        for(int i = 0; i < n; i++)
        {
            eVector1[0][i] = eVector1[0][i] / maxE1 + 0;
        }
        for(int i = 0; i < n; i++)
        {
            eVector2[0][i] = eVector2[0][i] / maxE2 + 0;
        }
        printf("\nThe eigenvector is:\n");
        for(int i = 0; i < n; i++)
        {
            printf("%.15lf\n", eVector1[0][i]);
        }
        printf("\n");
        for(int i = 0; i < n; i++)
        {
            printf("%.15lf\n", eVector2[0][i]);
        }
    }
    if(Case == 4)
    {
        double V[1][10], AV[1][10], A1V[1][10];
        for(int i = 0; i < n; i++)
        {
            V[0][i] = B[step][i];
        }
        for(int i = 0; i < n; i++)
        {
            AV[0][i] = 0;
            for(int j = 0; j < n; j++)
            {
                AV[0][i] = AV[0][i] + A[i][j] * V[0][j];
            }
        }
        for(int i = 0; i < n; i++)
        {
            A1V[0][i] = 0;
            for(int j = 0; j < n; j++)
            {
                A1V[0][i] = A1V[0][i] + A[i][j] * AV[0][j];
            }
        }
        double a1 = A1V[0][0];
        double a2 = A1V[0][1];
        double b1 = AV[0][0];
        double b2 = AV[0][1];
        double c1 = V[0][0];
        double c2 = V[0][1];
        double a = 1;
        double b = (a1 * c2 - c1 * a2) / (c1 * b2 - b1 * c2);
        double c = (a2 * b1 - a1 * b2) / (c1 * b2 - b1 * c2);
        printf("\n");
        printf("Expression: z^2 + %lfz + %lf = 0\n",b, c);
        double delta = b * b - 4 * a * c;
        if(delta >= 0)
        {
            printf("Delta is bigger than 0\n");
        }
        else
        {
            double real_eValue = - b / (2 * a);
            double im_eValue = sqrt(-delta) / (2 * a);
            double eValue1[1][2];
            eValue1[0][0] = real_eValue;
            eValue1[0][1] = im_eValue;
            double eValue2[1][2];
            eValue2[0][0] = real_eValue;
            eValue2[0][1] = - im_eValue;
            printf("The first eigenvalue is: %lf + %lfi\n", eValue1[0][0], eValue1[0][1]);
            printf("The second eigenvalue is: %lf %lfi\n", eValue2[0][0], eValue2[0][1]);
            double eVectorReal[1][10], eVector1Im[1][10], eVector2Im[1][10];
            for(int i = 0; i < n; i++)
            {
                eVectorReal[0][i] = A1V[0][i] + eValue1[0][0] * AV[0][i];
                eVector1Im[0][i] = A1V[0][i] + eValue1[0][1] * AV[0][i];
                eVector2Im[0][i] = A1V[0][i] + eValue2[0][1] * AV[0][i];
            }
            printf("\nThe first eigenvector is:\n");
            for(int i = 0; i < n; i++)
            {
                printf("%lf + %lf\n", eVectorReal[0][i], eVector1Im[0][i]);
            }
            printf("\n");
            printf("The second eigenvector is:\n");
            for(int i = 0; i < n; i++)
            {
                printf("%lf %lf\n", eVectorReal[0][i], eVector2Im[0][i]);
            }
        }
    }
    return 0;
}