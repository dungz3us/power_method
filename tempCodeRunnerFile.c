if(Case == 4)
    {
        double V[1][10], AV[1][10], A1V[1][10];
        for(int i = 0; i < n; i++)
        {
            V[0][i] = B[step][i];
        }
        for(int i = 0; i < n; i++)
        {
            printf("%lf\n", V[0][i]);
        }
        printf("\n");
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
            printf("%lf\n", AV[0][i]);
        }
        printf("\n");
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
            printf("%lf\n", A1V[0][i]);
        }
        printf("\n");
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
            printf("The first eigenvalue is: %lf + %lfi\n", real_eValue, im_eValue);
            printf("The second eigenvalue is: %lf %lfi\n", real_eValue, -im_eValue);
            double eVectorReal[1][10], eVectorIm[1][10];
            for(int i = 0; i < n; i++)
            {
                eVectorReal[0][i] = A1V[0][i] - real_eValue * AV[0][i];
                eVectorIm[0][i] = 0 - im_eValue * AV[0][i];
            }
            printf("\nThe first eigenvector is:\n");
            for(int i = 0; i < n; i++)
            {
                printf("%lf + %lfi\n", eVectorReal[0][i], eVectorIm[0][i]);
            }
            printf("\n");
            printf("The second eigenvector is:\n");
            for(int i = 0; i < n; i++)
            {
                printf("%lf + %lfi\n", eVectorReal[0][i], -eVectorIm[0][i]);
            }
        }