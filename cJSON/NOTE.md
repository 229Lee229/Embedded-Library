// @author: Lee
// @date: 29-Noveber-2024


Cjson source code address: 
https://github.com/DaveGamble/cJSON/tree/master



// The following is the code to test whether the cjson format is correct
// The following is the code to test whether the cjson format is correct. In the Keil MDK compilation environment, when nested in cjson, such as the "Payload" nested in the following text, the nested data needs to be escaped with the escape character '\' in order to be successfully recognized by cjson. c
// The cJSON_GetErrPtr() function will return a pointer indicating unsuccessful parsing

```c
 char *test_cJSON_Parse = "{\"Type\":4,\"Time\":1721824139120,\"MsgId\":\"b51b9c69-deb0-4e4d-b2e4-eb7294266b50\",\"SendId\":\"SVR01\",\"Payload\":\"{\\\"CtxId\\\":\\\"7f91c5a9f0879994d95a42e919b574af\\\"}\"}";
cJSON * jo = cJSON_Parse(test_cJSON_Parse);
if (jo) {
	printf("JSON ok\n");
}
else{
	printf("JSON parse error: %s\n", cJSON_GetErrorPtr());
}
cJSON_Delete(jo);			
return 0;	
```



// Analyze cjson instance code

// Here is an example of cjson

>    { "Type": 101,
>
>     "Time": 1744533467325,
>
>     "MsgId": "4af325ke4af325ke4af325ke4af325ke",
>
>     "SendId": "SVR01",
>
>     "Payload": {"Start": 1744533467325,"End": 1732885200000,"Getter": "clientId_001"}}

```c
		cJSON *jo = cJSON_Parse((char *)json_temp);

		if (jo == NULL) {
			printf("JSON parse error: %s\n", cJSON_GetErrorPtr());
			cJSON_Delete(jo);
			return;
		}else printf("Json OK\r\n");
		
		
		cJSON *type = cJSON_GetObjectItem(jo, "Type");
		cJSON *time = cJSON_GetObjectItem(jo, "Time");
		cJSON *msgId = cJSON_GetObjectItem(jo, "MsgId");
		cJSON *sendId = cJSON_GetObjectItem(jo, "SendId");
		cJSON *payload = cJSON_GetObjectItem(jo, "Payload");
		
		
		
		if (type && time && msgId && sendId && payload){
			printf("Type: %d\n", type->valueint);
			printf("Time: %.llf\n", time->valuedouble);  
			printf("MsgId: %s\n", msgId->valuestring);
			printf("SendId: %s\n", sendId->valuestring);
			
			char payload_json_string[256];
			sprintf(payload_json_string,"%s",payload->valuestring);
			long long Current_time_stamp;
				switch(type->valueint){
					
					case HeartBeat_Syn:
                        		// ... 
								break;
					case RELAY_AllOn_EXC_1:			
                        		// ...
								break;
					case RELAY_1_ON:
                        		// ...                        
								break;
					case RELAY_1_OFF:		
                        		// ...						
								break;
					case SysReset:
                        		// ...
								break;
					
					case 0:		
                        		// ...
								break;
					default:
                        		// ...
								break;
					
				}
			
			
			
		cJSON_Delete(jo);
            
         //   Extract nested JSON 
		cJSON *payload_json = cJSON_Parse(payload_json_string);
        if (payload_json == NULL) {
            printf("Payload JSON parse error: %s\n", cJSON_GetErrorPtr());
            cJSON_Delete(payload_json);
            return;
        }else printf("Payload JSON OK!\r\n");		
		
		
		cJSON *Start  = cJSON_GetObjectItem(payload_json, "Start");
		cJSON *End 	  = cJSON_GetObjectItem(payload_json, "End");
		cJSON *Getter = cJSON_GetObjectItem(payload_json, "Getter");
        if (Start && End && Getter) {
            printf("Start: %.llf\n", Start->valuedouble);
			printf("End:%.llf\n",	 End  ->valuedouble);
			printf("Getter:%s\n",	 Getter->valuestring);
        }else{	
			printf("Start error!\r\n");	
        }
		
		cJSON_Delete(payload_json);		
		}else cJSON_Delete(jo);
	
	
	
		return;

```

