#include "a_samp"
#include "sscanf2"

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

GetColumn(fmt[], select){
	new arr[10][32];
	sscanf(fmt, "p<|>a<s[32]>[10]", arr);
	if(isnull(arr[select])){
		format(arr[select], 32, "Error: unknown column");
	}
	return arr[select];
}

GetMaxColumns(fmt[]){
	new increment;
	new length = strlen(fmt);
	if(length < 1) return -1;
	for(new i; i < length; i++){
		if(length > 0 && increment == 0 && i == length){
			//increment++;
			break;
		}
		if(fmt[i] == '|'){
			increment++;
		}
	}
	return increment+1;
}

UpdateColumn(_str[], replace[], pos){
	new str[512];
	new result_find = strfind(_str, "|", true);
	format(str, sizeof str, "%s", _str);
	new pos_limiter, pos_rank;
	GetLimiters(str, pos, pos_limiter, pos_rank);
	if(result_find == -1){
		strdel(str, pos_limiter, pos_rank);
		strins(str, replace, pos_limiter);
		return str;
	}
	if(!pos){
		strdel(str, pos_limiter, pos_rank-1);
		strins(str, replace, pos_limiter);
	}else{
		strdel(str, pos_limiter+1, pos_rank);
		strins(str, replace, pos_limiter+1);
	}
	return str;
}
