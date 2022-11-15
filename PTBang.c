#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const int ERROR_STATE = 100;
#define MAX 100
#define MAX_COL 256
typedef int state;            // kieu cac trang thai
typedef unsigned char *attri; // kieu cua thuoc tinh
typedef unsigned char *token; // kieu cua tu to
unsigned char *x;             // xau vao x ()
unsigned int i = 0;           // vi tri cua ky tu doc trong xau x
int table[MAX][MAX];
int state_get_space[] = {1, 3, 5, 7, 9, 12};

unsigned char readchar(unsigned char *x, unsigned int i) // unsigned char : các số nguyên dương từ 0 đến 255
{
    // tra ve ky tu tiep theo, tương ứng với kí tự thứ i
    //    printf("i= %d , c= %c",i,*(x + i));
    if (i < strlen(x)) {
        return (*(x + i));
    }
    else {
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
    case 39:
    case 41:
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
    case 6:
    case 10:
    case 13:
    case 17:
    case 18:
    case 21:
    case 22:
    case 25:
    case 28:
    case 30:
    case 38:
    case 40:
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
        strcpy(ch, "so sanh khac");
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
    case 38:
        strcpy(ch, "dich phai roi gan");
        break;
    case 39:
        strcpy(ch, "dich phai");
        break;
    case 40:
        strcpy(ch, "dich trai roi gan");
        break;
    case 41:
        strcpy(ch, "dich trai");
        break;
    default:
        strcpy(ch, "token ko duoc doan nhan(tt ko dung \0");
    }
    return ch;
}
void catchar_in_token(unsigned char c, token tk)
{
    // ghep them ky tu c vao cho tu to tk
    *(tk + strlen(tk) + 1) = '\0';
    *(tk + strlen(tk)) = c;
}
void remove_space() // cat ky tu trang
{
	unsigned char **chuoi=&x; // con tro tro den con tro
	
    unsigned char result[500]; // mang luu ket qua
    int pos = 0;
    int i;
    for (i = 0; i < strlen(*chuoi); i++) { // duyet chuoi
        if (*(*(chuoi) + i) == ' ' || *(*(chuoi) + i) == '\n' || *(*(chuoi) + i) == 'r') { // nếu là kí tự trắng
            
            continue;
        }
        else {
            result[pos++] = *(*(chuoi) + i); // gán kí tự vào mảng kết quả
        }
    }
    result[pos] = '\0'; // kết thúc chuỗi
    *chuoi = result; // gán chuỗi kết quả cho chuỗi ban đầu
    
}
token search_token(unsigned int *i, attri tt) { // tim kiem token
    // tra ve tri tu vung cua tu to bdau tu vi tri i, thuoc tinh tra ve cho tt
    // token tk = _token1;
    char tokenTemp[1000] = "";
    token tk = tokenTemp;
    unsigned char c;
    state s = 0, cs; // trang thai hien tai, trang thai tiep theo
    // cắt ký tự trắng bỏ
    //  remove_space();
    // printf("%s",x);
    // 1 vong do cat duoc 1 tu to 
    do {

        do
        {
            c = readchar(x, *i);
            // printf("Doc ki tu c: %c\n", c);
            // printf("Vi tri i: %d\n", *i);
            *i = *i + 1;
            
            int isSpace = 0;
            // c = ' '
            if(c == ' ' || c == '\n') {
                int length = sizeof state_get_space / sizeof(int);
                int j;
                // printf("length = %d\n", length);
                for(j = 0; j < length; j++) {
                    if(s == state_get_space[j]) {
                    // printf("Lay khoang trang\n");
                        isSpace = 1;
                        break;
                    }
                }
            }
            if(isSpace == 1) { break; }
        } while ((c == ' ') && (*i < strlen(x)));

        
        cs = table[s][c]; // trạng thái tiếp theo
        // printf("----- s = %d, c = %c, cs = %d -------", s, c, cs);
        if (cs == ERROR_STATE) {
            printf("loi tai vi tri % i", *i);
            tk = "Error";
            break;
        }

        else if (star_end_state(cs)) {
            strcpy(tt, attribute(cs));
            break;
        }
        else if (nostar_end_state(cs)) {
            catchar_in_token(c, tk); 
            *i=*i+1;
            strcpy(tt, attribute(cs));
            break;
        }
        else if (*i > (strlen(x) - 1)) {
            printf("het xau vao, ko roi vao TT ket thuc");
            tk = "Error";
            break;
        }
        else {
            catchar_in_token(c, tk);
            // *i=*i+1;
            s = cs;
        }
    } while (1);
    return tk;
}
void create_table()
{
    // tao bang chuyen trang thai table
    // Đọc file thành table

    int i, j;
    // Khoi tao tat ca cac o trong table co trang thai ERROR_STATE
    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < MAX_COL; j++)
        {
            table[i][j] = ERROR_STATE;
        }
    }

    FILE *fp;
    char fname[] = "tableNew.txt";
    fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("Loi mo file");
        exit(1);
    }
    
    int state, next; // state: trạng thái vao, next : trạng thái tiep theo
    unsigned char *c;
    unsigned char *t; // kí tự đọc vào

    // read file into the table
    while (fscanf(fp, "%d %s %d", &state, &c, &next) != EOF)
    {
        if (strcmp((const char *)&c, "khac") == 0)
        {
            int i;
            for (i = 0; i < MAX_COL; i++)
            {
                table[state][i] = next;
            }
        }
        else if (strcmp((const char *)&c, "enter") == 0)
        {
            table[state][10] = next;
        }
        else if (strlen((const char *)&c) == 3)
        {
            t = &c;
            unsigned char k;
            for (k = *t; k <= *(t + 2); k++)
            {
                table[state][(unsigned char)k] = next;
            }
        }
        else
        {
            table[state][(unsigned char)c] = next;
        }
    }

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
    attri a =_att;
    create_table();
    do {
        printf("\ni= %d", i);
        tk = search_token(&i, a);
        if (strcmp(tk, "Error") != 0) {
            printf("\n Token : %s", tk);
            printf("\n Attribute : %s", a);
            save_token_and_attribute(tk, a);
            printf("\n");
        }
        else {
            // printf("\nToken: %s", tk);
            break;
        }
        
    } while ((*tk != '\0') && (i < strlen(x)));
}

void input() {
	// Nhap xau vao x
	x = (unsigned char *)malloc(150 * sizeof(unsigned char)); 
    // printf("Nhap vao xau: ");
    // fgets(x, 150, stdin);
    x = ">= > >>= >> <= <* >! ";
}


int main()
{
    input();
    lexical_analysis();
    return 0;
}
