// mytitle.c (2017 5/28)
// Modified by renlai@xojh
 
#include <ansi.h>
inherit F_CLEAN_UP;
private void confirm_title(string titleno,object me,mapping inq2);

int main(object me, string arg)
{
	 int i=0;
     mapping inq;
     string str="", *indexs;
		
	if( !arg )
	{
	    write(sprintf("%s\n", me->short(1)));
	    return 1;
	}
	if (arg=="all")
	{
		
	   if(mapp(inq=me->query("mytitle/quest")))		   
	    {
			
                indexs=keys(inq);
                for(i=0;i<sizeof(indexs);i++)
                        {
                                str=i+"--"+me->query("mytitle/quest/"+indexs[i])+" \n"+str;
                        }
                str="��Ŀǰӵ�е�ͷ������: \n"+str+"\n";
	str = replace_string(str, "HBMAG",HBMAG);
	str = replace_string(str, "HBYEL",HBYEL);
	str = replace_string(str, "HBBLU",HBBLU);
	str = replace_string(str, "HBWHT",HBWHT);
	str = replace_string(str, "HBRED",HBRED);
	str = replace_string(str, "HBGRN",HBGRN);
	str = replace_string(str, "HBCYN",HBCYN);
	str = replace_string(str, "RED",RED);
	str = replace_string(str, "GRN", GRN);
	str = replace_string(str, "YEL", YEL);
	str = replace_string(str, "BLU", BLU);
	str = replace_string(str, "MAG", MAG);
	str = replace_string(str, "CYN", CYN);
	str = replace_string(str, "WHT", WHT);
	str = replace_string(str, "HIR", HIR);
	str = replace_string(str, "HIG", HIG);
	str = replace_string(str, "HIY", HIY);
	str = replace_string(str, "HIB", HIB);
	str = replace_string(str, "HIM", HIM);
	str = replace_string(str, "HIC", HIC);
	str = replace_string(str, "HIW", HIW);
	
	str = replace_string(str, "NOR", NOR);
	str = replace_string(str, "+","");
	str = replace_string(str, "\"","");
	
                write(str);
				write("��ѡ��ͷ�����:");
				input_to("confirm_title",me,inq);
				write("ͷ���޸ĳɹ���\n");
		        return 1;
				
        }
		else return notify_fail("��δ��ÿ�ѡͷ�Ρ�\n");		
	}
	
}

private void confirm_title(string titleno,object me)
{
	 int count,j=0;
	 mapping inq2;
	 string temp,*indexs2;      
	 
if(mapp(inq2=me->query("mytitle/quest")))		   
   {
	 indexs2=keys(inq2);	 
	 count=sizeof(indexs2);
	 
	 if (!sscanf(titleno, "%d", j) || j >=count || j < 0) 
	 {
		write("\n��ֵ����\n");
        return;		
	 }
		
		temp=me->query("mytitle/quest/"+indexs2[j]);
	temp = replace_string(temp, "HBMAG",HBMAG);
	temp = replace_string(temp, "HBYEL",HBYEL);
	temp = replace_string(temp, "HBBLU",HBBLU);
	temp = replace_string(temp, "HBWHT",HBWHT);
	temp = replace_string(temp, "HBRED",HBRED);
	temp = replace_string(temp, "HBGRN",HBGRN);
	temp = replace_string(temp, "HBCYN",HBCYN);
	temp = replace_string(temp, "RED", RED);
	temp= replace_string(temp, "GRN", GRN);
	temp= replace_string(temp, "YEL", YEL);
	temp= replace_string(temp, "BLU", BLU);
	temp= replace_string(temp, "MAG", MAG);
	temp= replace_string(temp, "CYN", CYN);
	temp= replace_string(temp, "WHT", WHT);
	temp= replace_string(temp, "HIR", HIR);
	temp= replace_string(temp, "HIG", HIG);
	temp= replace_string(temp, "HIY", HIY);
	temp= replace_string(temp, "HIB", HIB);
	temp= replace_string(temp, "HIM", HIM);
	temp= replace_string(temp, "HIC", HIC);
	temp= replace_string(temp, "HIW", HIW);
	
	temp= replace_string(temp, "NOR", NOR);
	temp= replace_string(temp, "+","");
	temp= replace_string(temp, "\"","");
		 write("��ѡ����:"+temp);
		 me->set("title",temp);
	}   
   return;		 
	}
 
int help(object me)
{
	if(wizardp(me)) 
	write(@HELP
ָ���ʽ: mytitle [all]
 
��ʾ��ӵ�е�ͷ�Ρ�
 
HELP
	);
	else write(@HELP
ָ���ʽ: mytitle
 
��ʾ����ӵ�е�ͷ�Ρ�
 
HELP
	);
}
