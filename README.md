# Delimiters
```c++
public OnGamemodeInit(){
	new fmt[64] = "Colum1|Colum2|Colum3";
	printf("fmt %s", fmt);
	//output "Colum1|Colum2|Colum3"
	
	printf("strins %s", AddColum(fmt, "Colum4"));
	//output "Colum1|Colum2|Colum3|Colum4"
	
	printf("DeleteColum %s", DeleteColum(fmt, 4));
	//output "Colum1|Colum2|Colum3"
	
	new count = GetMaxColumns(fmt);
	//output 3
	
	GetColumn(fmt, 2);
	//output Colum2
}
```
