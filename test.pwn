
#define FMT_LIMIT 512
GetLimiters(fmt[], slot, &pos_limiter, &pos_rank){
	new increment,
		length = strlen(fmt),
		result_find = strfind(fmt, "|", true);
	if(length == 0) return 0;
	for(new i; i < length; i++){
		if(fmt[i] == '|' && result_find != -1){
			if(slot == 0){
				pos_rank = i+1;
				pos_limiter = 0;
				break;
			}
			increment++;
			if(increment == slot){
				pos_limiter = i; //-> |
				for(new a = i+1; a < strlen(fmt); a++){
					if(fmt[a] == '|'){
						pos_rank = a; //-> pos
						break;
					}else if(length-1 == a){
						pos_rank = a+1;
						break;
					}
				}
				break;
			}
		}else if(result_find == -1){
			if(slot == 0){
				pos_limiter = 0;
				pos_rank = length;
				break;
			}else{
				pos_limiter = length;
				pos_rank = 0;
			}
			break;
		}
	}
	return 1;
}

DeleteColum(_str[], select){
	new fmt[FMT_LIMIT];
	new pos_limiter, pos_rank;
	GetLimiters(_str, select, pos_limiter, pos_rank);
	strdel(_str, pos_limiter, pos_rank);
	format(fmt, FMT_LIMIT, "%s", _str);
	return fmt;
}

AddColum(const fmt[], const add[]){
	new _str[FMT_LIMIT];
	format(_str, FMT_LIMIT, "%s|%s", fmt, add);
	return _str;
}

#include "a_samp"

public OnGamemodeInit(){
	new fmt[64] = "Colum1|Colum2|Colum3";
	printf("fmt %s", fmt);
	printf("strins %s", AddColum(fmt, "Colum4"));
	//output "Colum1|Colum2|Colum3|Colum4"
	
	printf("DeleteColum %s", DeleteColum(fmt, 4));
	//output "Colum1|Colum2|Colum3"
}
