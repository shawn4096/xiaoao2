// info command.
// by snowman@SJ 1998.
//by renlai@xa2 2016 ����꿨�¿���������

#include <ansi.h>
#include <localtime.h>
inherit F_CLEAN_UP;
#include <canpian.h>

// #define TIME_TICK ((time()-945630720)*60)
mixed main(object me)
{
	object *ob;
	int i,ppl_cnt = 0, cnt = 0, wcnt = 0, f_cnt = 0, u_cnt = 0, i_cnt,scard=0,ycard=0,mcard=0,fcard=0,freeu=0;
    int hama3=0;
	string file;
	mapping *notes;
	mapping note;
	string test="suibo-zhuliu|dodge";
   string cur_value,next_value;
   string *myvalue;
   string* skilllist;
   object canpian;
	//ob = filter_array(objects(), (: userp :));
    ob=users();

	i = sizeof(ob);
	while( i-- ) {
		//&& (ob[i]->query("env/invisibility"))=="YES"
            if (wizardp(ob[i])) wcnt++;
		else if (interactive(ob[i])){
			 ppl_cnt++;
			 if(ob[i]->is_fighting()) f_cnt++;
			 if(!living(ob[i])) u_cnt++;
			 if(ob[i]->query("buyvip")) {ob[i]->delete("freeuser");scard++;}
			 if(ob[i]->query("y-card-vip")) {ob[i]->delete("freeuser");ycard++;}
			 if(ob[i]->query("m-card-vip")) {ob[i]->delete("freeuser");mcard++;}
			 if(ob[i]->query("freeuser")) freeu++;
			 if(query_idle(ob[i]) > 120) i_cnt++;
			 if(userp(ob[i])&& !wizardp(ob[i]) && !(ob[i]->query("no_pk")) && ob[i]->query("quest/hama/nizhuan/pass"))
             {
				 hama3++;
				 write(ob[i]->query("id"));		
                 //write("msg"+!ob[i]->query("no_pk"));					 
			 }				 
			 }
		else cnt++;
	}
	     fcard=ppl_cnt-scard-ycard-mcard-freeu;
		 if (fcard<0) fcard=0;
   
   
    
	
	
	
	
	write("\n"+MUD_NAME+"Ŀǰ���� "+wcnt+" λ��ʦ�� "+ppl_cnt+" λ��������У�"+cnt+" λ��Ҷ����С�
���У�
			��ս�����У� "+f_cnt+" λ��
			���Ի�˯�����У� "+u_cnt+" λ��
			�������У� "+i_cnt+" λ��
			�����У� "+scard+" λ��
			�꿨�У� "+ycard+" λ��
			�¿��У� "+mcard+" λ��
			�����ң� "+freeu+" λ��
			ע������ң� "+fcard+" λ��
			���3���: "+hama3+" λ��
          
ϵͳ������"+query_load_average()+"��
���ڵ� time() �ǣ�" + time() + "��
���ڵ� Natured time() �ǣ�" + TIME_TICK + " " + localtime(TIME_TICK)[2] + ":" + localtime(TIME_TICK)[1]+"��
���ڵ� uptime() �ǣ�" + uptime() + "��
Natured ��ʱ���ǣ�" + NATURE_D->query_daytime() + "��\n\n");
	return 1;
}




int help(object me)
{
write(@HELP
ָ���ʽ : users

���ָ������г�Ŀǰ�����������

���ָ� who
HELP
	);
	return 1;
}
