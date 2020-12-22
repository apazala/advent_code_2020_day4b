#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fieldnamestree[26][26][26];
int eyecolorstree[26][26][26];

char fieldnames[7][4] = {
	"byr",
	"iyr",
	"eyr",
	"hgt",
	"hcl",
	"ecl",
	"pid"
};

char eyecolors[7][4] = {
	"amb",
	"blu",
	"brn",
	"gry",
	"grn",
	"hzl",
	"oth"
};

void init() {
	for (int i = 0; i < 7; i++) {
		fieldnamestree[fieldnames[i][0] - 'a'][fieldnames[i][1] - 'a'][fieldnames[i][2] - 'a'] = (i+1);
	}
	for (int i = 0; i < 7; i++) {
		eyecolorstree[eyecolors[i][0] - 'a'][eyecolors[i][1] - 'a'][eyecolors[i][2] - 'a'] = (i + 1);
	}
}


char line[1024];
char fieldvalue[256];
int main() {

	FILE *fin = fopen("input.txt", "r");
	if (!fin) {
		fprintf(stderr, "unable to open file\n");
		return 1;
	}

	init();

	int nvalid = 0;
	int count = 0;
	while (fgets(line, 1024, fin)) {
		if (line[0] == '\n') {//count and reset
			if (count >= 7)
				nvalid++;
			count = 0;
		}
		else {

			int intvalue;
			char *endptr;

			for (char *pcolon = strchr(line, ':'); pcolon; pcolon = strchr(pcolon + 1, ':')) {
				sscanf(pcolon + 1, "%s", fieldvalue);
				switch (fieldnamestree[pcolon[-3] - 'a'][pcolon[-2] - 'a'][pcolon[-1] - 'a'])
				{
				case 1:
					intvalue = strtol(fieldvalue, &endptr, 10);
					if (*endptr == '\0' && intvalue >= 1920 && intvalue <= 2002)
						count++;
					break;

				case 2:					
					intvalue = strtol(fieldvalue, &endptr, 10);
					if (*endptr == '\0' && intvalue >= 2010 && intvalue <= 2020)
						count++;
					break;

				case 3:
					intvalue = strtol(fieldvalue, &endptr, 10);
					if (*endptr == '\0' && intvalue >= 2020 && intvalue <= 2030)
						count++;
					break;

				case 4:					
					intvalue = strtol(fieldvalue, &endptr, 10);
					if (endptr != fieldvalue) {
						if (strcmp(endptr, "cm") == 0 && intvalue >= 150 && intvalue <= 193)
							count++;
						else if (strcmp(endptr, "in") == 0 && intvalue >= 59 && intvalue <= 76)
							count++;
					}
					break;

				case 5:
					if (fieldvalue[0] == '#' && (strlen(fieldvalue+1) == 6)) {
						intvalue = strtol(fieldvalue+1, &endptr, 16);
						if (*endptr == '\0')
							count++;
					}

					break;

				case 6:
					if (strlen(fieldvalue) == 3 && eyecolorstree[fieldvalue[0] - 'a'][fieldvalue[1] - 'a'][fieldvalue[2] - 'a'])
						count++;
					break;

				case 7:					
					if (strlen(fieldvalue) == 9) {
						intvalue = strtol(fieldvalue + 1, &endptr, 10);

						if (*endptr == '\0')
							count++;
				}

					break;

				}
			}

		}
	}

	if (count >= 7) //last passport may not end with empty line
		nvalid++;

	printf("%d\n", nvalid);

	fclose(fin);
	return 0;
}