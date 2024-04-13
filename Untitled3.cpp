#include <stdio.h>
#include <stdlib.h>

// Khai bao cau truc MaTran
struct MaTran {
    int **data; // Con tro hai chieu den cac phan tu cua ma tran
    int hang;   // So hang cua ma tran
    int cot;    // So cot cua ma tran
};

// Ham nhap ma tran tu nguoi dung
struct MaTran nhapMaTran() {
    struct MaTran mt;
    printf("Nhap so hang cua ma tran: ");
    scanf("%d", &mt.hang);
    printf("Nhap so cot cua ma tran: ");
    scanf("%d", &mt.cot);

    // Cap phat bo nho cho ma tran
    mt.data = (int **)malloc(mt.hang * sizeof(int *));
    for (int i = 0; i < mt.hang; ++i) {
        mt.data[i] = (int *)malloc(mt.cot * sizeof(int));
    }

    printf("Nhap cac phan tu cua ma tran:\n");
    for (int i = 0; i < mt.hang; ++i) {
        for (int j = 0; j < mt.cot; ++j) {
            printf("Nhap phan tu tai hang %d cot %d: ", i + 1, j + 1);
            scanf("%d", &mt.data[i][j]);
        }
    }
    return mt;
}

// Ham in ma tran 
void inMaTran(struct MaTran mt) {
    printf("Ma tran:\n");
    for (int i = 0; i < mt.hang; ++i) {
        for (int j = 0; j < mt.cot; ++j) {
            printf("%d ", mt.data[i][j]);
        }
        printf("\n");
    }
}

// Ham giai phong bo nho da cap phat cho ma tran
void giaiPhongMaTran(struct MaTran mt) {
    for (int i = 0; i < mt.hang; ++i) {
        free(mt.data[i]);
    }
    free(mt.data);
}

// Ham cong hai ma tran
struct MaTran congMaTran(struct MaTran mt1, struct MaTran mt2) {
    struct MaTran ketQua;
    if (mt1.hang != mt2.hang || mt1.cot != mt2.cot) {
        printf("Hai ma tran khong cung kich thuoc, khong the cong!\n");
        ketQua.data = NULL;
        ketQua.hang = ketQua.cot = 0;
        return ketQua;
    }

    ketQua.hang = mt1.hang;
    ketQua.cot = mt1.cot;

    // Cap phat bo nho cho ma tran ket qua 
    ketQua.data = (int **)malloc(ketQua.hang * sizeof(int *));
    for (int i = 0; i < ketQua.hang; ++i) {
        ketQua.data[i] = (int *)malloc(ketQua.cot * sizeof(int));
    }

    // Thuc hien cong tung phan tu cua hai ma tran
    for (int i = 0; i < ketQua.hang; ++i) {
        for (int j = 0; j < ketQua.cot; ++j) {
            ketQua.data[i][j] = mt1.data[i][j] + mt2.data[i][j];
        }
    }

    return ketQua;
}

// Ham nhan vo huong ma tran voi mot so nguyen
struct MaTran nhanVoHuong(struct MaTran mt, int scalar) {
    struct MaTran ketQua;
    ketQua.hang = mt.hang;
    ketQua.cot = mt.cot;

    // Cap phat bo nho cho ma tran ket qua 
    ketQua.data = (int **)malloc(ketQua.hang * sizeof(int *));
    for (int i = 0; i < ketQua.hang; ++i) {
        ketQua.data[i] = (int *)malloc(ketQua.cot * sizeof(int));
    }

    // Thuc hien nhan tung phan tu cua ma tran voi scalar
    for (int i = 0; i < ketQua.hang; ++i) {
        for (int j = 0; j < ketQua.cot; ++j) {
            ketQua.data[i][j] = mt.data[i][j] * scalar;
        }
    }

    return ketQua;
}

// Ham nhan hai ma tran
struct MaTran nhanHaiMaTran(struct MaTran mt1, struct MaTran mt2) {
    struct MaTran ketQua;
    if (mt1.cot != mt2.hang) {
        printf("So cot cua ma tran thu nhat khong bang so hang cua ma tran thu hai, khong the nhan hai ma tran!\n");
        ketQua.data = NULL;
        ketQua.hang = ketQua.cot = 0;
        return ketQua;
    }

    ketQua.hang = mt1.hang;
    ketQua.cot = mt2.cot;

    // Cap phat bo nho cho ma tran ket qua 
    ketQua.data = (int **)malloc(ketQua.hang * sizeof(int *));
    for (int i = 0; i < ketQua.hang; ++i) {
        ketQua.data[i] = (int *)malloc(ketQua.cot * sizeof(int));
    }

    // Thuc hien phep nhan hai ma tran
    for (int i = 0; i < ketQua.hang; ++i) {
        for (int j = 0; j < ketQua.cot; ++j) {
            ketQua.data[i][j] = 0;
            for (int k = 0; k < mt1.cot; ++k) {
                ketQua.data[i][j] += mt1.data[i][k] * mt2.data[k][j];
            }
        }
    }

    return ketQua;
}

// Ham hoan doi hai hang cua ma tran
void hoanDoiHang(struct MaTran mt, int hang1, int hang2) {
    if (hang1 >= mt.hang || hang2 >= mt.hang) {
        printf("Hang nhap vao khong hop le!\n");
        return;
    }
    int *temp = mt.data[hang1];
    mt.data[hang1] = mt.data[hang2];
    mt.data[hang2] = temp;
}

int main() {
    printf("Nhap ma tran thu nhat:\n");
    struct MaTran mt1 = nhapMaTran();
    printf("Nhap ma tran thu hai:\n");
    struct MaTran mt2 = nhapMaTran();

    printf("Ma tran thu nhat:\n");
    inMaTran(mt1);
    printf("Ma tran thu hai:\n");
    inMaTran(mt2);

    struct MaTran tong = congMaTran(mt1, mt2);
    if (tong.data != NULL) {
        printf("Tong hai ma tran:\n");
        inMaTran(tong);
        giaiPhongMaTran(tong);
    }

    int scalar;
    printf("Nhap so nguyen vao de nhan voi ma tran thu nhat: ");
    scanf("%d", &scalar);
    struct MaTran tichVoHuong = nhanVoHuong(mt1, scalar);
    printf("Tich vo huong cua ma tran thu nhat voi %d:\n", scalar);
    inMaTran(tichVoHuong);
    giaiPhongMaTran(tichVoHuong);

    struct MaTran tich = nhanHaiMaTran(mt1, mt2);
    if (tich.data != NULL) {
        printf("Tich hai ma tran:\n");
        inMaTran(tich);
        giaiPhongMaTran(tich);
    }

    int hang1, hang2;
    printf("Nhap hai hang muon hoan doi trong ma tran thu nhat: ");
    scanf("%d %d", &hang1, &hang2);
    hoanDoiHang(mt1, hang1 - 1, hang2 - 1);
    printf("Ma tran thu nhat sau khi hoan doi hai hang:\n");
    inMaTran(mt1);

    // Giai phong bo nho da cap phat cho ma tran
    giaiPhongMaTran(mt1);
    giaiPhongMaTran(mt2);

    return 0;
}

