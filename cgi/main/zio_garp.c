#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void main(int argc, char *argv[]){
	printf("Content-type : text/html\n\n");
	FILE* fp;
	printf("<HTML><head><style>table, th, td {    border: 1px solid black;    border-collapse: collapse;}th, td {    padding: 5px;    text-align: left;    }</style></head><body><table>  <tr>	<th>INDEX</td>    <th>Name</td>    <th>Device MAC[1]</td>     <th>Device MAC[2]</td>    <th>Delete</td>  </tr>");
	if (fp = fopen("/www/DeviceList", "r")){
		char* str = (char*)malloc(sizeof(char) * 1024);
		char* name = (char*)malloc(sizeof(char) * 944);
		char* one = (char*)malloc(sizeof(char) * 40);
		char* two = (char*)malloc(sizeof(char) * 40);
		int i = 0;
		while(fgets(str, 1024, fp)){
			sscanf(str, "%s %s %s", name, one, two);
			printf("<tr><td>%d</td>", i);
			printf("<td>%s</td>", name);
			printf("<td>%s</td>", one);
			printf("<td>%s</td>", two);
			printf("<td><button onclick=\"window.location.href='./lockerListDel?in=%d'\">del</button></td></tr>", i++);
		}
		fclose(fp);
		free(str);
		free(name);
		free(one);
		free(two);
	}
	printf("</table><fieldset><legend>CONNECT LIST</legend><table>  <tr>    <th>IP</th>    <th>MAC</td>   </tr>");
	if(fp = fopen("/proc/net/arp", "r")){
		char* str = (char*)malloc(sizeof(char) * 1024);
		char* ip = (char*)malloc(sizeof(char) * 40);
		char* mac = (char*)malloc(sizeof(char) * 40);
		int i = 0;
		while(fgets(str, 1024, fp)){
			if(i == 0){
				i = -1;
				continue;
			}
			sscanf(str, "%s %*s %*s %s %*s %*s", ip, mac);
			printf("<tr><td>%s</td>", ip);
			printf("<td>%s</td></tr>", mac);
		}
		free(str);
		free(ip);
		free(mac);
	}
	printf("</table></fieldset><form action=\"./lockerListAdd\">  <fieldset>    <legend>Append Device</legend>    name:<br>    <input type=\"text\" placeholder=\"name\" required name=\"name\">    <br>    Device MAC[1]:<br>    <input type=\"text\" placeholder=\"xx:xx:xx:xx:xx:xx\" required name=\"mac1\">    <br>    Device MAC[2]:<br>    <input type=\"text\" placeholder=\"xx:xx:xx:xx:xx:xx\" required name=\"mac2\">	<br>    <input type=\"submit\" value=\"Submit\">  </fieldset></form></body></HTML>");
	exit(0);
}

