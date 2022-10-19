/*
	Copyright (c) d13g0
    	Discord d13g0#3444
*/

#include "a_samp"
#include "sscanf2"

#define FMT_LIMIT 512
stock GetLimiters(const fmt[], slot, &start_pos, &end_pos, const limiter[] = "|"){
	new 
		increment,
		length = strlen(fmt),
		result_find = strfind(fmt, limiter[0], true);
	if(length == 0) return 0;
	for(new i; i < length; i++){ 
		if(fmt[i] == limiter[0] && result_find != -1){
			if(slot == 0){ 
				end_pos = i+1;
				start_pos = 0; 
				break; 
			}
			increment++; 
			if(increment == slot){
				start_pos = i;
				for(new a = i+1; a < strlen(fmt); a++){
					if(fmt[a] == limiter[0]){
						end_pos = a;
						break;
					}else if(length-1 == a){
						end_pos = a+1;
						break;
					}
				}
				break;
			}
		}else if(result_find == -1){
			if(slot == 0){
				start_pos = 0;
				end_pos = length;
				break;
			}else{
				start_pos = length;
				end_pos = 0;
			}
			break;
		}
	}
	return 1;
}

stock DeleteColum(_str[], select){
	new fmt[FMT_LIMIT], pos_limiter, pos_rank;
	GetLimiters(_str, select, pos_limiter, pos_rank);
	strdel(_str, pos_limiter, pos_rank);
	format(fmt, FMT_LIMIT, "%s", _str);
	return fmt;
}

stock AddColum(const fmt[], const add[], const limiter[] = "|"){
	new _str[FMT_LIMIT];
	if(strlen(fmt) < 1) format(_str, FMT_LIMIT, "%s", add);
	else format(_str, FMT_LIMIT, "%s%s%s", fmt, limiter[0], add);
	return _str;
}

stock GetColumn(const fmt[], select, const limiter[] = "|"){
	new arr[10][512], str[64];
	format(str, sizeof str, "p<%s>a<s[512]>[10]", limiter[0]);
	sscanf(fmt, str, arr);
	if(isnull(arr[select])){
		format(arr[select], 32, "Error: unknown column");
	}
	return arr[select];
}

stock UpdateColumn(const fmt[], const update[], pos, const limiter[] = "|"){
	new start_pos, end_pos, str[512];
	format(str, sizeof str, "%s", fmt);
	new max_c = GetMaxColumns(str)-1;
	GetLimiters(fmt, pos, start_pos, end_pos, limiter[0]);
	if(pos > 0){
		if(max_c > 0){
			if(pos != max_c){
				if(pos == max_c-1) end_pos--;
				end_pos++;
			}
		}else end_pos--;
		start_pos++;
	}else{
		if(max_c > 0) end_pos--;
	}
	strdel(str, start_pos, end_pos);
	strins(str, update, start_pos);
	return str;
}

stock GetMaxColumns(const fmt[], const delimiter[] = "|"){
	new increment;
	new length = strlen(fmt);
	new result_find = strfind(fmt, delimiter[0], true);
	if(fmt[result_find] == delimiter[0]) increment++;
	strfind(fmt, delimiter[0], false);
	if(length < 1) return -1;
	for(new i; i < length; i++){
		if(fmt[i] == delimiter[0]){
			increment++;
		}
		if(length > 0 && increment == 0 && i == length-1){
			increment++;
			break;
		}
	}
	return increment;
}

stock ConvertTimeStamp(time, &minutes, &seconds){
	if(gettime()-time <= 0){
		seconds = time-gettime();
		if(seconds > 60) {
			minutes = seconds/60;
		}
		seconds = seconds-minutes*60;
	}else seconds = minutes = 0;
	return 0;
}
