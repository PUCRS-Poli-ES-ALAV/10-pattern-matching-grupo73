#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linked-list.c"


char* read_file_to_string(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read != file_size) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[file_size] = '\0'; // Null-terminate the string

    fclose(file);
    return buffer;
}

long patternMatchingBasico(char* s1, char* s2)
{
    int count = 0;
    char* p1 = s1;
    char* p2 = s2;
    while (1)
    {
        count++;
        if(*(p2) == '\0')
        {
            printf("Basico: %d\n",count);
            return (p1 - s1)/sizeof(char) - (p2 - s2)/sizeof(char);
        }
        if(*(p1) == '\0')
        {
            printf("Basico: %d\n",count);
            return -1;
        }

        if (*(p1) == *(p2))
        {
            p1++;
            p2++;
        }
        else
        {
            int dif = (p2 - s2)/sizeof(char);
            p1 -= dif;
            p1++;
            p2 = s2;
        }
    }
    printf("Basico: %d\n",count);
}

long patternMatchingMemoizacao(char* s1, char* s2)
{
    long count = 0;
    char* p1 = s1;
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    Node* n = malloc(sizeof(Node));
    n->next = NULL;
    n->value = -1;
    n->start_pos = -1;
    LinkedList occupied = {1,n};

    while (1)
    {
        count++;
        if (*(p1) == '\0') break;

        for (size_t i = 1; i < occupied.size; i++)
        {
            count++;
            Node* n = get(&occupied,i);
            int value = n->value;
            //printf("%d\n",i);
            if (s2[value] == *(p1))
            {
                n->value++;
                if (n->value == len2)
                {
                    printf("Memoizacao: %ld %d\n",count, occupied.size);
                    return n->start_pos;
                }
            }
            else
            {
                n->value = -1;
                expel(&occupied,i);
            }
        }

        if (*(p1) == s2[0] && len1 - (p1 - s1)/sizeof(char) <= len2)
        {
            //É um começo
            append(&occupied,1,(p1 - s1)/sizeof(char));
        }

        p1++;
    }
    printf("Memoizacao: %ld %d\n",count, occupied.size);
    return -1;
}

int main()
{
    char* lorem_ipsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus interdum mi at ante pharetra, in aliquet justo dignissim. Phasellus vitae ipsum non orci malesuada ultrices id a orci. Duis sed turpis tincidunt, commodo turpis vitae, interdum enim. Proin vel urna nec massa pellentesque imperdiet. Suspendisse rutrum erat in ante varius, vitae commodo nunc tristique. Sed finibus, lectus at gravida mollis, nisl urna condimentum augue, sit amet tristique mauris orci et ex. Sed arcu dui, condimentum eu porttitor in, mollis sit amet mi. Donec facilisis pharetra ligula volutpat blandit. Maecenas pellentesque lacus sit amet eros malesuada, imperdiet commodo augue aliquam. Vivamus rhoncus nisl metus, ac tempus nisl placerat ac.";
    char* lorem_ipsum_20 = " Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin a nisl odio. Proin luctus laoreet porttitor. Donec tincidunt urna tincidunt purus euismod, vel commodo metus consectetur. Praesent rhoncus arcu velit, vel condimentum magna auctor in. Curabitur pulvinar hendrerit velit in tincidunt. Donec consequat sagittis elit et vehicula. Morbi dignissim velit at scelerisque bibendum. Nulla convallis nulla nec metus pretium porta. Etiam vitae pretium nibh. Sed in orci elit. Cras convallis lectus sed arcu sollicitudin hendrerit. Nulla lacinia metus non magna feugiat, commodo convallis erat molestie. Etiam feugiat est et dui pellentesque, quis rutrum mauris vestibulum.  Nunc consequat ornare ultrices. Nulla facilisi. Morbi eu faucibus purus, ac vulputate ligula. Proin bibendum iaculis nunc in ultrices. Proin consectetur ex at turpis dapibus gravida. Maecenas iaculis ante et ex efficitur tincidunt. In et sapien id augue convallis molestie sit amet in ligula. Vestibulum non urna sit amet nulla aliquam tristique. Aenean gravida nunc tellus, id efficitur urna luctus eget. Aenean molestie vehicula felis nec mattis. Donec ante sem, lacinia rutrum orci id, pulvinar pretium risus. Vestibulum eget elit nec neque ullamcorper accumsan. In purus ligula, accumsan nec ligula ut, cursus tempor purus. Suspendisse ante nisl, porta sed dui vitae, pharetra ornare arcu. Pellentesque iaculis quam mi, sit amet aliquet eros sodales eu.  Donec sed leo nec lacus bibendum ultricies. Duis tempus dolor non sem tincidunt sagittis. Phasellus quis tempus nulla, vitae mattis nisi. Etiam mollis nec libero non posuere. Fusce rhoncus ut nulla nec rhoncus. Vivamus pellentesque odio vel sollicitudin molestie. Proin velit quam, dignissim at rutrum quis, sollicitudin a arcu. Maecenas posuere lacinia elit, vel eleifend dui tempus in.  Quisque nec sem vitae felis egestas eleifend. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Integer luctus rhoncus quam at tincidunt. Vivamus justo nisl, elementum id massa non, ornare pellentesque mauris. Sed eget ullamcorper tellus. Praesent aliquet imperdiet elit, quis tristique augue rhoncus vitae. Nunc et justo nulla. Cras sem eros, ultricies aliquet faucibus scelerisque, scelerisque laoreet leo. Aenean nulla mi, suscipit id erat quis, consequat hendrerit nisi. In ut urna dapibus justo condimentum mattis. Proin ipsum mauris, cursus ac auctor sit amet, viverra vel turpis. Praesent ullamcorper vestibulum ipsum, ut tempus eros varius vel. Nulla a feugiat nisi. Nunc posuere, libero quis aliquam sollicitudin, magna dolor dignissim eros, ut efficitur dui ante sit amet dolor. Etiam ut metus rhoncus, ornare urna a, convallis ligula.  Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Sed pretium tincidunt tempus. Vestibulum dictum dictum justo volutpat venenatis. Aliquam lacinia laoreet arcu. Curabitur condimentum finibus justo sit amet imperdiet. Pellentesque eget tortor ipsum. Pellentesque sit amet lorem arcu.  Etiam id pellentesque nulla. Nullam non ultrices eros, vel finibus nunc. Proin viverra ultrices massa sit amet dictum. In eu turpis vel turpis tempus condimentum in eu neque. Sed turpis libero, lacinia at ullamcorper in, hendrerit ac odio. Cras bibendum vehicula tristique. Integer vestibulum finibus lectus eu cursus. Sed ultrices pharetra sem, eu pretium justo aliquet id. Donec dignissim arcu bibendum, sollicitudin leo sed, egestas tellus. Cras accumsan congue risus. Phasellus congue massa eu ligula lobortis convallis. Nullam commodo urna a purus pellentesque congue. Aliquam et elit lacus.  Nulla aliquam ipsum eu nunc convallis, nec sagittis ante scelerisque. Etiam ut blandit urna. Vestibulum tincidunt suscipit erat, non tristique urna facilisis ut. Aenean sit amet magna nec velit condimentum semper. Duis ut tincidunt turpis. Nam faucibus urna lacus, eget ornare nulla luctus bibendum. Phasellus commodo, lectus vitae tristique luctus, magna nunc finibus sapien, at mattis nibh leo id turpis. Morbi condimentum, dolor blandit aliquet scelerisque, sapien metus volutpat ligula, eu sagittis diam nulla non metus. Fusce viverra euismod vulputate. Aenean fringilla felis ut orci ullamcorper convallis.  Nullam consectetur non urna in blandit. Etiam pharetra ipsum vel orci pretium, ac efficitur nulla sodales. Ut maximus bibendum tortor, nec luctus leo gravida sit amet. Duis ut feugiat libero. Quisque luctus, dui mollis luctus sollicitudin, ex ante eleifend metus, id pharetra sem magna eu elit. Vestibulum facilisis a eros quis hendrerit. Aliquam eleifend dui in facilisis molestie. In facilisis laoreet massa eget congue. Curabitur a tincidunt massa, eget dignissim nunc. Donec ultricies consequat urna in laoreet. Cras at urna placerat, congue massa vel, ornare risus. Duis non tincidunt lectus.  Aliquam non urna sed augue facilisis scelerisque ac commodo elit. Maecenas placerat diam quis enim pellentesque gravida. Maecenas fringilla sem at lorem fringilla vestibulum. Quisque volutpat nisl vel maximus venenatis. Praesent tortor turpis, vehicula at viverra in, efficitur a erat. Donec ullamcorper egestas erat ac finibus. Nam vel pellentesque purus. Cras sodales felis nec lacus ornare vestibulum. Sed lorem mi, gravida at mi at, facilisis auctor nisi. Vivamus dignissim justo sollicitudin, euismod eros in, lobortis tortor.  Maecenas ut enim enim. Curabitur tincidunt dictum lectus in dapibus. Integer a fringilla leo. Nunc vitae sapien magna. Sed sollicitudin fermentum sapien non ornare. Mauris luctus ultrices massa, at lobortis eros efficitur vel. Nam efficitur suscipit sem a ultrices. Nullam molestie volutpat ullamcorper. Integer at congue odio. Ut porttitor sagittis odio, non finibus sapien accumsan ut. Nam eleifend, ante eget euismod convallis, enim magna congue diam, ac commodo eros sem quis enim. Nulla dapibus pharetra ex, sed venenatis purus pulvinar ut. Proin mi sapien, mattis sit amet sem eget, pretium hendrerit risus. Donec eget lectus ullamcorper eros pharetra semper ut ac est. Mauris semper, ex vel malesuada ullamcorper, tortor magna vulputate velit, quis eleifend nisi orci in dolor. Praesent vel sapien turpis.  Aliquam aliquet arcu sapien, id porttitor ipsum blandit nec. Fusce dictum mi eu turpis posuere congue. Quisque suscipit mollis risus in placerat. Proin metus dui, congue vitae rhoncus nec, luctus non diam. Proin placerat quam elit, sit amet sodales est semper et. Sed a ipsum sit amet augue placerat pharetra. Mauris et mauris libero. Suspendisse nisi odio, faucibus et imperdiet hendrerit, eleifend lobortis lorem. In sagittis eleifend magna, ac luctus lectus tempor at. Duis finibus vulputate felis non eleifend. Pellentesque porttitor faucibus lacus quis maximus. Aliquam mollis enim a ipsum semper cursus.  Aliquam erat volutpat. Integer varius dignissim nunc. Fusce iaculis lectus eu cursus rutrum. Praesent vehicula luctus augue, eget pretium lacus pellentesque vitae. Pellentesque scelerisque id quam sagittis molestie. Donec hendrerit volutpat posuere. Integer maximus rutrum pulvinar.  Nam hendrerit in lectus quis sodales. Cras ultricies quam blandit, dignissim mi ut, maximus risus. Phasellus rhoncus iaculis velit sed luctus. Vestibulum in congue ex, vitae porta orci. Morbi ut leo vel lorem rutrum vestibulum at quis leo. Suspendisse elementum pharetra libero non vestibulum. Aliquam nulla neque, ullamcorper vel congue suscipit, gravida ut eros. Phasellus lectus metus, tempus ut augue a, auctor fringilla erat. Suspendisse elementum pharetra nisi eu pretium. Quisque libero enim, rutrum vel eleifend sit amet, porta sed quam. Sed sed ex non elit cursus condimentum. Morbi eu elit eget ex hendrerit feugiat in ut odio.";
    char* bible = read_file_to_string("bible.txt");
    clock_t start = clock();
    long momoi = patternMatchingMemoizacao(bible,bible+4000000);
    clock_t end = clock();
    double timeelapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo: %lf\n%ld\n", timeelapsed, momoi);


    start = clock();
    long basic = patternMatchingBasico(bible,bible+4000000);
    end = clock();
    timeelapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo: %lf\n%ld\n", timeelapsed, basic);
    return 0;
}