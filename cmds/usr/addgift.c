//Create by jpei 2010
#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
    int gifts, max_gifts;
    string gifts_name;

    max_gifts = me->query("relife/gifts/now");

    if(!arg){
        tell_object(me,"��ʹ�á�"+HIG+"addgift �츳���� to �츳��������"+NOR+"�����з���!\n\n"NOR);
        write("�����츳����������Ϊ��"HIW"����"NOR"����"HIY"����"NOR"����"HIM"��"NOR"����"HIC"����"NOR"���� \n\n"NOR);
        return 1;
    }

    if(!sscanf(arg, "%d to %s", gifts, gifts_name)){
        tell_object(me,"��ʹ�á�addgift �츳���� to �츳�������ơ����з��䣡\n"NOR);
        write("�����츳����������Ϊ�������������ǡ������������ԡ��� \n"NOR);
        return 1;
    }
    else{
        if(gifts<1)
            return notify_fail("�����Ӳ����ͷ�����ˣ�\n");

        if(gifts > max_gifts)
            return notify_fail("������û��ô���츳�������Է��䣡\n����scoreָ�����鿴������ӵ�ж��ٿɷ����츳������\n");
//����
        if(gifts_name == "����" || gifts_name == "����" || gifts_name == "str" ){
               if((int)me->query("str",1)> 50 - gifts)
               return notify_fail("�����츳��಻�ܳ���50�㣡������ѡ��\n"NOR);
           
               me->add("str",gifts);
               me->add("relife/gifts/now",-gifts);
               me->add("relife/gifts/used",gifts);
               tell_object(me,"�㽫"+HIW+chinese_number(gifts)+NOR+"���츳���䵽�ˡ�"+HIR+"����"+NOR+"���ϣ�\n");
               return 1;
        }

 
//����
        if(gifts_name == "����"|| gifts_name == "con"){
            if((int)me->query("con",1)>50 - gifts)
               return notify_fail("�����츳��಻�ܳ���50�㣡������ѡ��\n"NOR);
            me->add("con",gifts);
            me->add("relife/gifts/now",-gifts);
            me->add("relife/gifts/used",gifts);
            tell_object(me,"�㽫"+HIW+chinese_number(gifts)+NOR+"���츳���䵽�ˡ�"+HIR+"����"+NOR+"���ϣ�\n");
            return 1;
        }
//��
        if(gifts_name == "��" || gifts_name == "dex"){
            if((int)me->query("dex",1)>50 - gifts)
               return notify_fail("�����츳��಻�ܳ���50�㣡������ѡ��\n"NOR);
            me->add("dex",gifts);
            me->add("relife/gifts/now",-gifts);
            me->add("relife/gifts/used",gifts);
            tell_object(me,"�㽫"+HIW+chinese_number(gifts)+NOR+"���츳���䵽�ˡ�"+HIR+"��"+NOR+"���ϣ�\n");
            return 1;
        }


//����
        if(gifts_name == "����" ||gifts_name == "int"){
            if((int)me->query("int",1)>50 - gifts)
               return notify_fail("�����츳��಻�ܳ���50�㣡������ѡ��\n"NOR);
            me->add("int",gifts);
            me->add("relife/gifts/now",-gifts);
            me->add("relife/gifts/used",gifts);
            tell_object(me,"�㽫"+HIW+chinese_number(gifts)+NOR+"���츳���䵽�ˡ�"+HIR+"����"+NOR+"���ϣ�\n");
            return 1;
        }

        //������
        return notify_fail("��ѡ����ȷ���츳����������츳������ָ���ʽ��\n"+HIR+"giftadd �츳���� to �츳�������� "+NOR+"!\n");
         }
        return 1;
}
