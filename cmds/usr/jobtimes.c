//jobtimes by River@SJ 2003.6
//modify by linux@sj 2003.10.23

#include <ansi.h>
 
inherit F_CLEAN_UP;
/*                me->add("xx_points", 1);           /d/xingxiu/npc/ding.c mmd ̫����cat����

     ws  dead ws û������¼ wo kao slogan stal     
     teach monk �Ҳ��� :(     
*/
mapping *job_type=({
        (["job_name" : "��Ĺ�䳲",
     "job_long" : "��Ĺ�䳲����"]),
     (["job_name" : "��Ĺ��Ĺ",
     "job_long" : "��Ĺ��ĹѲ������"]),
     (["job_name" : "����Ѳ��",
     "job_long" : "����Ѳ������"]),
     (["job_name" : "��������",
     "job_long" : "������������"]),
     (["job_name" : "�һ���",                              //thd����һ��job�������һ�����Ĺ->�һ���
     "job_long" : "�һ�����Ĺɱ������"]),
     (["job_name" : "����",
     "job_long" : "��������"]),
     (["job_name" : "����Ԫ��",
     "job_long" : "���ҿ�Ԫ����"]),
     (["job_name" : "����ͭ��",
     "job_long" : "�䵱����ͭ������"]),
     (["job_name" : "��ɽ��ʯ",
     "job_long" : "��ɽ��ʯ����"]),
     (["job_name" : "��ɽ����",
     "job_long" : "��ɽ��������"]),
//������
     (["job_name" : "�����л�",
     "job_long" : "�����л�����"]),
     (["job_name" : "��������",
     "job_long" : "������������"]),
     (["job_name" : "��������ս",
      "job_long" : HIB"��������ս����"NOR]),
      (["job_name" : "����ѵ��",
      "job_long" : RED"������ѵ������"NOR]),
      (["job_name" : "������ҩ",
      "job_long" : "��������ҩ����"]),
     (["job_name" : "������ҩ",
      "job_long" : "��������ҩ����"]),

     (["job_name" : "ץ��",
     "job_long" : "ؤ��׽������"]),
         (["job_name" : "�ٸ�",
         "job_long" : "�ٸ�������׷������"]),              
  //������
       (["job_name" : "���ְ���",
         "job_long" : "���ְ�������"]),
       (["job_name" : "���ֲ˵�",       
         "job_long" : "���ֲ˵�����"]),                                 
       (["job_name" : "������ֵ",                               //����->������ֵ ���ֺ����־�Ԯ�����ͻ������Ҳ���ܴ�����ֵ������������
         "job_long" : "������ֵ����"]),
       (["job_name" : "�𷨽�ħ",
         "job_long" : "���ֶ�����������"]),
       (["job_name" : "�޺���",                                // ������ �޺������񣬼����ֽ̺�������
         "job_long" : "�޺���ֵ�ڽ�ϰ����"]),
       (["job_name" : "���ִ���",
         "job_long" : HIC"�������޴�������"NOR]), 		 
       
       (["job_name" : "���־�Ԯ",
         "job_long" : HIC"���־�Ԯ����"NOR]),  
         //(["job_name" : "����",
         //"job_long" : HIC"���־�Ԯ����"NOR]),  ���� һ�������˾�Ԯjob �ּӱ�� ���־�Ԯ  ����Ŀǰֻ�ܴ����ܵ�job Ciwei@SJ     
	//ؤ��
		(["job_name" : "ؤ��",
         "job_long" : "ؤ���ⳤ��ɱ������"]),
         
       (["job_name" : "��ɱ",
         "job_long" : RED"��ɱճ��������"NOR]),
	   (["job_name" : "���ϳ�",
         "job_long" : NOR"���ղ��ϳ�"NOR]),      
	   (["job_name" : "��Ħ��",
         "job_long" : WHT"Ӣ�ۿ�����Ħ��"NOR]),
  
       (["job_name" : "���",
         "job_long" : "������ݴ�������"]),
//ȫ��job
       (["job_name" : "ȫ���ҩ",
         "job_long" : "ȫ��̲�ҩ����"]),

       (["job_name" : "������Ĺ",
         "job_long" : "ȫ���������Ĺ����"]),       
       (["job_name" : "ȫ�����",
         "job_long" : "ȫ��̳�������"]),    	   
	   (["job_name" : "ȫ������",
         "job_long" : "ȫ����������"]),      
	   (["job_name" : "�ɹ�����",
         "job_long" : "�����ɹ���������"]),      
//������

	   //�ɹ�	  
	   (["job_name" : "����",
         "job_long" : "��������ץ������",]),
         
       (["job_name" : "Ѳ��",
         "job_long" : "��������Ѳ������"]),

       (["job_name" : "�漱",
         "job_long" : HIR"�߹ظ漱����"NOR]),
         

        
       (["job_name" : "������ͽ",
         "job_long" : MAG"���޻�ɱ��ͽ����"NOR]),
         
       (["job_name" : "���ް���",
         "job_long" : HIY"���ް�ҩ����"NOR]),
         
        (["job_name" : "����",
         "job_long" : HIM"�������ɷ�������"NOR]),//add by Ciwei@SJ
         
       (["job_name" : "��ɽ",
         "job_long" : HIC"��ɽ����Ⱥ�Ͷ���������"NOR]),
         
       (["job_name" : "���߹�",
         "job_long" : "���߹�"HIY"���˭������÷"NOR"����"]),
         
       (["job_name" : "����",
         "job_long" : "�����ھֻ�������"]),
         
       (["job_name" : "����",
         "job_long" : HIY"����������������"NOR]),
         
       (["job_name" : "��ʯ",
         "job_long" : "�ƺӲ�ʯ����"]),
 //��ɽ
	   (["job_name" : "��ɽ��а",
         "job_long" : HIC"��ɽѰ��а��������"NOR]),       
       (["job_name" : "��ɽ",
         "job_long" : HIM"��ɽ�������ϲ�����"NOR]),
         
       (["job_name" : "����",
         "job_long" : HIB"���ݷ�������"NOR]),
	//������
       (["job_name" : "������ҩ",
         "job_long" : "���ؾ��������ҩ"]),
         (["job_name" : "����׷ɱ",
         "job_long" : "����׷ɱ��ϸ����"]),
     

       (["job_name" : "�䵱",                                       //�䵱->�䵱����
         "job_long" : "�䵱��Զ��ɱ��������"]),
//Ѫ��
        (["job_name" : "Ѫ������",
         "job_long" : "Ѫ����������"]),
         (["job_name" : "Ѫ������",
         "job_long" : "Ѫ�����ĵ��Ӿ�������"]),
         (["job_name" : "Ѫ�����",
         "job_long" : "Ѫ�����������������"]),
		
		 (["job_name" : "ѩ�ȼ�ս",
         "job_long" : "Ѫ��ѩ�ȼ�ս����"]),
       
		 (["job_name" : "ѩɽ",
         "job_long" : HIR"��������Ů����"NOR]),    
         
         (["job_name" : "�������ս",
         "job_long" : HIY"�������ս����"NOR]),       	
         	
         	
         	(["job_name" : "ȫ��̿������",
         "job_long" : HBRED"ȫ��̿������"NOR]),
         	
         	(["job_name" : "���������ɹŴ��",
         "job_long" : HIG"���������ɹŴ��"NOR]),
         
         
         (["job_name" : "���ְ�",
         "job_long" : HIY"���ְ�����"NOR]),
         
         (["job_name" : "��ػ�",
         "job_long" : HIG"��ػ�����"NOR]),
		 
		 (["job_name" : "���¸���",
         "job_long" : HIG"������̸�������"NOR]),
		 
		 (["job_name" : "�´�����",
         "job_long" : HIG"�´���������"NOR]),
		 
		  (["job_name" : "Χ��������",
         "job_long" : HIG"Χ������������"NOR]),
         
         (["job_name" : "����",
         "job_long" : HIR"������������"NOR]),
         
         (["job_name" : "Ľ��",                                 //Ľ��͵ѧ->Ľ��
         "job_long" : HIW"Ľ��͵ѧ����"NOR]),
         
         (["job_name" : "���ǵ�",
         "job_long" : HIY"���ǵ�ʤ����������"NOR]),
		  (["job_name" : "�ͽ�����",
         "job_long" : HIY"������ʦ�ͽ�����"NOR]),
		(["job_name" : "��������",
         "job_long" : HIY"����ʯ��������"NOR]),         
		(["job_name" : "������",
		"job_long" : HIY"����������"NOR]),
});


int main(object me,string arg)
{
        object ob;
        string str;
        int j, i;

        if (!userp(me)) return 0;
        seteuid(getuid(me));

        if (!arg) ob = me;
        else if (!objectp(ob = present(arg, environment(me)))) {
                if (wizardp(me) ) {
                        if (!ob) ob = LOGIN_D->find_body(arg);
                        if (!ob) ob = find_living(arg);
                        if (!ob) return notify_fail("��Ҫ�쿴˭�����������\n");
                        if (wiz_level(me) < wiz_level(ob))
                                return notify_fail("��Ҫ�쿴˭�����������\n");
                }
        }
        if (!wizardp(me) && me!=ob)
                return notify_fail("��Ҫ�쿴˭�����������\n");

        if (ob->is_corpse() || !ob->is_character())
                return notify_fail("�ǲ��ǻ���Ү��\n");
        if (!userp(ob))
                return notify_fail("�ǲ�����ң���������\n");
        if(!ob->query("job_time"))
                return notify_fail((ob!=me?ob->name(1):"��")+"����û����ɹ��κ�����\n");

        str = (ob!=me?ob->name(1):"��")+"��ɵ�����������£�\n";
        str +="�����������������������������������Щ��������������Щ�����������������\n";
        str +="��           "HIW"��������"NOR"             �� "HIW"��ǰ�������"NOR" �� "HIW"�ϴ��콱����¼"NOR" ��\n";
        str +="�����������������������������������੤�������������੤����������������\n";
        
        //Job_Type=keys(job_type);
        i = sizeof(job_type);
        
        for (j =0; j < i ;j++)
        if (ob->query("job_time/"+job_type[j]["job_name"]))
                str += sprintf("��%-32s��   %-11s��    %-12s��\n",job_type[j]["job_long"],
                sprintf("%d ��",ob->query("job_time/"+job_type[j]["job_name"])),
                (intp(ob->query("job_last_gift/"+job_type[j]["job_name"])) && ob->query("job_last_gift/"+job_type[j]["job_name"])!=0 )?sprintf("%d ��",ob->query("job_last_gift/"+job_type[j]["job_name"])):HIG"�޼�¼"NOR);
                
        str +="�����������������������������������ة��������������ة�����������������\n";
        
        if(stringp(ob->query("job_name")))  str +=HIW""+ (ob!=me?ob->name(1):"��")+"����������"+ob->query("job_name")+"����\n"NOR;
        
        tell_object(me, str);
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ�� jobtimes
           jobtimes <��������>             (��ʦר��)

���ָ�������ʾ���Ѿ���ɵĸ������������

���ָ�score

        Copyright 1997-2003 ShuJian MUD Wizard Group.
        All rights reserved.

        Visit our Homepage at - www.mymud.com

HELP
        );
        return 1;
}
