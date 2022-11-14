#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const int ERROR_STATE = 100;
#define MAX 100
typedef int state;            // kieu cac trang thai
typedef unsigned char *attri; // kieu cua thuoc tinh
typedef unsigned char *token; // kieu cua tu to
unsigned char *x;             // xau vao x ()
unsigned int i = 0;           // vi tri cua ky tu doc trong xau x
int table[MAX][MAX];
char _token1[100000] = " ";

unsigned char readchar(unsigned char *x, unsigned int i) // unsigned char : các số nguyên dương từ 0 đến 255
{
    // tra ve ky tu tiep theo, tương ứng với kí tự thứ i
    //    printf("i= %d , c= %c",i,*(x + i));
    if (i < strlen(x))
    {

        return (*(x + i));
    }
    else
    {
        return ('\0'); // \0 : null, được định nghĩa là 1 kí tự null- đó là 1 kí tự mà các bit đặt thành 0, sử dụng để chấm dứt chuỗi
    }
}

int star_end_state(state s)
{
    // kiểm tra s có phải là trạng thái kết thúc sao không ( tức trạng thái kết thúc trả lui kí tự vừa đọc) - các trạng thái kết thúc có dấu sao
    switch (s)
    {
    case 4:
    case 8:
    case 11:
    case 14:
    case 19:
    case 23:
    case 26:
    case 29:
        return 1;
    default:
        return 0;
    }
}
int nostar_end_state(state s)
{
    // kiểm tra s có phải là trạng thái kết thúc sao không - trả về 1 nếu không thuôc trạng thái sao
    switch (s)
    {
    case 2:
    case 3:
    case 6:
    case 7:
    case 10:
    case 13:
    case 17:
    case 18:
    case 21:
    case 22:
    case 25:
    case 28:
    case 30:
        return 1;
    default:
        return 0;
    }
}
attri attribute(state s)
{
    // trả về thuộc tính tương ứng với trạng thái kết thúc
    // trả về thuộc tính của từ tố ( dựa vô ottomat) khi otomat rơi vào trạng thái kết thúc
    char *ch = (char *)malloc(sizeof(char));
    switch (s)
    {
    case 2:
        strcpy(ch, "so sanh lon hon bang");
        break;
    case 3:
        strcpy(ch, "dich phai");
        break;
    case 4:
        strcpy(ch, "so sanh lon hon");
        break;
    case 6:
        strcpy(ch, "so sanh nho hon bang");
        break;
    case 7:
        strcpy(ch, "dich trai");
        break;
    case 8:
        strcpy(ch, "so sanh nho hon");
        break;
    case 10:
        strcpy(ch, "so sanh khong bang");
        break;
    case 11:
        strcpy(ch, "phu dinh");
        break;
    case 13:
        strcpy(ch, "so sanh bang");
        break;
    case 14:
        strcpy(ch, "gan");
        break;
    case 17:
        strcpy(ch, "cong bang");
        break;
    case 18:
        strcpy(ch, "tang 1");
        break;
    case 19:
        strcpy(ch, "cong");
        break;
    case 21:
        strcpy(ch, "tru bang");
        break;
    case 22:
        strcpy(ch, "giam 1");
        break;
    case 23:
        strcpy(ch, "tru");
        break;
    case 25:
        strcpy(ch, "nhan bang");
        break;
    case 26:
        strcpy(ch, "nhan");
        break;
    case 28:
        strcpy(ch, "chia bang");
        break;
    case 29:
        strcpy(ch, "chia");
        break;
    case 30:
        strcpy(ch, "chia lay du");
        break;
    default:
        strcpy(ch, "token ko duoc doan nhan(tt ko dung \0");
    }
    return ch;
}
void catchar_in_token(unsigned char c, token tk)
{
    // ghep them ky tu c vao cho tu to tk
//    printf("\nDebug in 147 : TK = %s", tk);
    *(tk + strlen(tk) + 1) = '\0';
    *(tk + strlen(tk)) = c;
    //  printf("\n inchar = %s | ",*tk);
//    printf("\nDebug in 151 : TK = %s", tk);
}
void CatKiTuTrang()
{
	unsigned char **chuoi=&x;
	
    unsigned char result[500];
    int pos = 0;
    for (int i = 0; i < strlen(*chuoi); i++)
    {
        if (*(*(chuoi) + i) == ' ' || *(*(chuoi) + i) == '\n' || *(*(chuoi) + i) == 'r')
        {
            continue;
        }
        else
        {
            result[pos++] = *(*(chuoi) + i);
        }
    }
    result[pos] = '\0';
    *chuoi = result;
    
}
token search_token(unsigned int *i, attri tt)
{
    // tra ve tri tu vung cua tu to bdau tu vi tri i, thuoc tinh tra ve cho tt


    token tk = _token1;
    unsigned char c;
    state s = 0, cs;
    // cắt ký tự trắng bỏ
     CatKiTuTrang();
    // printf("%s",x);
    do
    {
        c = readchar(x, *i);
        int bb;
        switch (c)
        {
        case '>':
            bb = 0;
            break;
        case '=':
            bb = 1;
            break;
        case '<':
            bb = 2;
            break;
        case '+':
            bb = 3;
            break;
        case '-':
            bb = 4;
            break;
        case '*':
            bb = 5;
            break;
        case '/':
            bb = 6;
            break;
        case '%':
            bb = 7;
            break;
        }
        cs = table[s][bb];
        // printf("line183 : c = %c , cs = %d ", c, cs);
        if (cs == ERROR_STATE)
        {
            printf("loi tai vi tri % i", *i);
            tk = "Error";
            break;
        }

        else if (star_end_state(cs))
        {
            strcpy(tt, attribute(cs));
            break;
        }
        else if (nostar_end_state(cs))
        {
            catchar_in_token(c, tk);
             
            *i=*i+1;
            
            strcpy(tt, attribute(cs));
//            printf("\n 230 TK :%s , i= %d",tk,*i);
            break;
        }
        else if (*i >= (strlen(x) - 1))
        {
            printf("het xau vao, ko roi vao TT ket thuc");
            tk = "Error";
            break;
        }
        else
        {
            catchar_in_token(c, tk);
//            printf("\n243 TK :%s",tk);
            *i=*i+1;
            s = cs;
        }
    } while (1);
//    printf("Line 251 : Token = %s", tk);
    return tk;
}
void initTable(int table[][MAX])
{
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            table[i][j] = 100;
        }
    }
}
void create_table()
{
    // tao bang chuyen trang thai table
    // Đọc file thành table
    initTable(table);

    FILE *fp;
    char fname[] = "table.txt";
    int N = 256;
    char line[N];
    char str[16];
    fp = fopen(fname, "r");
    int a, c;
    char b;
    int bb;
    if (fp == NULL)
    {
        printf("%s file not open!\n", fname);
    }
    // init table
    int max = 50;

    while (fgets(line, N, fp) != NULL)
    {
        sscanf(line, "%d %c %d", &a, &b, &c);
        // printf("%d %c %d \n",a,b,c);
        switch (b)
        {
        case '>':
            bb = 0;
            break;
        case '=':
            bb = 1;
            break;
        case '<':
            bb = 2;
            break;
        case '+':
            bb = 3;
            break;
        case '-':
            bb = 4;
            break;
        case '*':
            bb = 5;
            break;
        case '/':
            bb = 6;
            break;
        case '%':
            bb = 7;
            break;
        }
        table[a][bb] = c;
    }
    // printf("> = < + - * / %\n");
    // for (int i = 0; i < 31; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //     {
    //         printf("%d ", table[i][j]);
    //     }
    //     printf("\n");
    // }

    fclose(fp);
}
void save_token_and_attribute(token tk, attri a)
{
    // luu tru tk,a vao danh sach
    // Lưu token vào danh sách → Xuất ra file
}
void lexical_analysis()
{
    char _token[10000] = " ";
    char _att[10000] = " ";
    token tk = _token;
    // printf("TOKEN334 = %s",tk);
    attri a=_att;
    create_table();
    do
    {
        printf("\ni= %d", i);
        tk = search_token(&i, a);
        printf("\n Token : %s", tk);
        printf("\n Attribute : %s", a);
        save_token_and_attribute(tk, a);
    } while ((*tk != '\0') && (i < strlen(x)));
}

void input() {
	// Nhap xau vao x
	x = (unsigned char *)malloc(150 * sizeof(unsigned char)); 
    printf("Nhap vao xau: ");
    fgets(x, 150, stdin);
}


int main()
{
    input();
    lexical_analysis();
    return 0;
}
