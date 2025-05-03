#include <stdio.h>
#include <stdlib.h>
typedef unsigned int DWORD;
typedef struct {
    double IPSValue;
    int sockets;            // CPU 소켓 수
    int cores_per_socket;   // 소켓당 코어 수
    double clock;           // 클럭 속도 (GHz 또는 Hz 단위)
    double ipc;             // cycle 당 instruction 수 (instructions per cycle)
} SystemSpec;

int main() {
    DWORD count;
    while (1) {
        printf("IPS 값을 구하기 위한 개체를 얼마나 생성할지 기입하시오: ");
        scanf("%u", &count);
        if(count!=0) {
            break;
        }
        else {
            printf("개체 수는 0이 될 수 없습니다. 다시 기입하십시오.\n\n");
        }
    }

    SystemSpec* systemSpec=calloc(count,sizeof(SystemSpec));
    if (systemSpec == NULL) {
        printf("메모리가 부족하여 개체를 할당할 수 없습니다. 엔터 키를 눌러 프로그램을 종료합니다.");
        system("pause");
        return -1;
    }
    for (DWORD i = 0;i < count;i++) {
        printf("%d번째 Sockets, Cores per Socket, Clock(GHz), Instructions per Cycle 값을 순서대로 기입하시오: ",i+1);
        scanf("%d %d %lf %lf",
            &((systemSpec + i)->sockets),
            &((systemSpec + i)->cores_per_socket),
            &((systemSpec + i)->clock),
            &((systemSpec + i)->ipc)
        );
    }
    for (DWORD i = 0;i < count;i++) {
        //개수*Hz*(instructions/cycle)=instructions/sec
        (systemSpec + i)->IPSValue =
            ((systemSpec + i)->sockets) *
            ((systemSpec + i)->cores_per_socket) *
            ((systemSpec + i)->clock) *
            ((systemSpec + i)->ipc);
    }
    printf("\n");
    for (DWORD i = 0;i < count;i++) {
        printf("Sockets: %d    Cores per Socket: %d    Clock: %lf(GHz)    Instructions per Cycle: %lf(IPC)        IPS: %lf(GIPS)\n",
            (systemSpec + i)->sockets,
            (systemSpec + i)->cores_per_socket,
            (systemSpec + i)->clock,
            (systemSpec + i)->ipc,
            (systemSpec + i)->IPSValue);
    }
    system("pause");

    free(systemSpec);
    return 0;
}
