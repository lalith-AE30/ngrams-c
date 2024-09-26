#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void load_dataset(float N[27][27]) {
  FILE *fp = fopen("names.txt", "r");
  char line[100];
  line[0] = 'a' - 1;
  while (fgets(line + 1, 99, fp)) {
    int len = strlen(line);
    line[len - 2] = 'a' - 1;

    for (int i = 1; i < len - 1; i++) {
      N[line[i - 1] - 'a' + 1][line[i] - 'a' + 1]++;
    }
  }
  fclose(fp);
}

void normalize(float N[27][27]) {
  for (int i = 0; i < 27; i++) {
    float sum = 0;
    for (int j = 0; j < 27; j++) {
      sum += N[i][j];
    }
    for (int j = 0; j < 27; j++) {
      N[i][j] /= sum;
    }
  }
}

char sample(float N[27][27], char c) {
  float r = (float)rand() / RAND_MAX;
  float sum = 0;
  for (int i = 0; i < 27; i++) {
    sum += N[c - 'a' + 1][i];
    if (r < sum) {
      return 'a' + i - 1;
    }
  }
  return 'a' - 1;
}

char* generate(float N[27][27]) {
  char name[100] = {'a' - 1};
  for (int len = 1; len < 100; len++) {
    char n = sample(N, name[len - 1]);
    name[len] = n;
    if (name[len] == 'a' - 1) {
      name[len] = '\0';
      break;
    }
  }
  return strdup(name + 1);
}

int main() {
  srand(time(NULL));
  float N[27][27] = {0};

  load_dataset(N);
  normalize(N);

  for (int i = 0; i < 10;) {
    char* name = generate(N);
    printf("%s\n", name + 1);
  }

  return 0;
}