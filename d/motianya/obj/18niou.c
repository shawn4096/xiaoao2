// 18niou.c
// by KinGSo
// ����-������

inherit ITEM;
#include <ansi.h>
void create()
{
        set_name(YEL"ʮ����ż"NOR, ({"shiba niou", "shiba", "niou", "shibaniou"}));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�װ���ʮ���޺���ɵ���ż���ݴ�������ż���������һ�Ÿ���ķ���ڹ��ķ���\n");
                set("value", 8000);
                set("unique", 1);
                set("material", "paper");
                set("no_give", "��ô���Ķ�������ɲ������ⶪ����\n");
                set("no_drop", "��ô���Ķ�������ɲ������ⶪ����\n");
                set("no_get", "�������������˵ı�������˯����Ҫ����ͷ�棬���޷���ȡ��\n");
                set("treasure", 1);
        }
}

void init()
{
        add_action("do_yanjiu", "yanxi");
}

int do_yanjiu(string arg)
{
        object me = this_player();
        object where = environment(me);
        int lhlevel, neili_lost;

        if(!id(arg)) return 0;

        if(me->query("gender") =="����")
                return notify_fail("���޸����ԣ�����������������������޺���ħ����\n");
                
        if(me->is_busy()) 
                return notify_fail("��������æ���ء�\n");
                
        if(query_temp("quest/Ħ����/luohan"))
                return notify_fail("�������͵���ģ��ɲ���͵��Ŷ��\n");
                
        if(me->is_fighting())
                return notify_fail("���޷���ս����ר�������ж���֪��\n");
        
        if((int)me->query_skill("shenzhao-jing", 1) >= 1 )
                return notify_fail("�㲻ɢȥ���վ�����ô�����޺���ħ����\n");
    
        if((int)me->query_skill("lengquan-shengong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ��Ȫ�񹦣���ô�����޺���ħ����\n");

        if((int)me->query_skill("kuihua-mogong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ����ħ������ô�����޺���ħ����\n");

       if((int)me->query_skill("kuihua-shengong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ�����񹦣���ô�����޺���ħ����\n");  
    
        if((int)me->query_skill("jiuyang-gong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ�����񹦣���ô�����޺���ħ����\n");  
     
       if((int)me->query_skill("hamagong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ��󡹦����ô�����޺���ħ����\n");

        if((int)me->query_skill("taixuan-gong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ̫��������ô�����޺���ħ����\n");       
                
        if(where->query("outdoors") != "Ħ���¶�" )
              return notify_fail("��ֻ����Ħ���¶����ܾ��������о�ʮ����ż��\n");
                
        if(me->query("jing") < 25)
                return notify_fail("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
                
        if(me->query_skill("force",1) < 100) 
                return notify_fail("����ڹ�����û�д�ã�����������\n");
                
       if ((int)me->query("int") < 33)
                return notify_fail("����������Բ������޷��о�ʮ����ż��\n");

       if ((int)me->query("con") < 20)
                return notify_fail("������ĸ��ǲ������޷��о�ʮ����ż��\n");

        if(this_object()->query("clone_by_wizard")) 
                return notify_fail("�������͵���ģ��ɲ���͵��Ŷ��\n");

        lhlevel = me->query_skill("luohan-fumogong", 1);
        if (lhlevel < 30)
                neili_lost = lhlevel / 2;
        else if (lhlevel< 70)
                neili_lost = lhlevel * 2 / 3;
        else if (lhlevel< 140)
                neili_lost = lhlevel * 3 / 4;
        else
                neili_lost = lhlevel ;
        if( neili_lost > 150) neili_lost = 150;
        if ( lhlevel >= (me->query_skill("force", 1) + 30))
                return notify_fail("��������ڹ��Ļ����������ٻ�ø���һ�����ߡ�\n");
        
        if (me->query("neili") < neili_lost) 
                return notify_fail("�������������޷�������ô������书��\n");
        if (me->query("combat_exp") < lhlevel * lhlevel * lhlevel / 10) 
                return notify_fail("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
        if (lhlevel >= 221 && me->query("neili") < lhlevel * 3 )
                return notify_fail("�����һ����ż����ʽ���ݹ�����£��⿿�ж����������������޷��ٻ�ý����ġ�\n");
        me->receive_damage("jing", 20);
        me->receive_damage("neili", neili_lost);
        if (!lhlevel ) {
                write(YEL"\��רע�Ķ��ŵ�һ����ż�������䶯������������ڼ�����֮����\n"NOR);
                write(YEL"�㶨һ���񣬴������ƣ�������̬�Ϲ۲죬���������ڼ����ɵķ��š�\n"NOR);
                write(YEL"�����㿪ʼ������ż�����ƣ�����������\n\n"NOR);
        }
        if (lhlevel >= 140)
                write("����ϸ�۲�����ż�����ƣ��ٶ���֮ǰͨ����ż��ϰ���������ţ�����е��ĵá�\n");
        else
                write("����ϰ��ʮ����ż���������ĵá�\n");
        me->improve_skill("luohan-fumogong", me->query_skill("force", 1));
        if (!random(9)) message("vision", me->name() + "����һ��ʮ����ż��ϸ���С�\n", environment(me), ({me}));
        if (me->query_skill("luohan-fumogong", 1) > lhlevel) {
                if (lhlevel == 29) {
                        write(YEL"\n����ϰ���˵�һ����ż������������ż���������Ż�����Ȼ�Ƚ����ף������а���֮����\n"NOR);
                        write(YEL"�㿪ʼ��ϰ�ڶ�����ż�����潲�����������������ķ��š�\n\n"NOR);
                }
                else if (lhlevel == 69) {
                        write(YEL"\n����ϰ���˵ڶ�����ż����Ȼ�����޺������ֵ��������������ķ��ţ�����������޺���ħ��ʵ�����������\n"NOR);
                        write(YEL"�㿪ʼ��ϰ��������ż��������ż�����ֵ���������Ҫ��\n\n"NOR);
                }
                else if (lhlevel == 139) {
                        write(YEL"\n����ϰ���˵�������ż����������Ҫ��Ϊ�������˺ô�ľ�����ȫ����ˡ�\n"NOR);
                        write(HBYEL HIR"żȻ��������һ�飬���˵����ȫ���鿪���㺧Ȼ����ԭ����Щ���˾�Ȼ�����㣬�ڲ���������ͬ������һ�����ľ���ͼ��\n\n"NOR);
                        write(HBYEL HIR"����ϸ�۲������б����ˡ����ס������ˣ���������ǵľ���ͼ������һ��ʮ�ָ�����ڹ��ķ���������Ͻ�����������������\n\n"NOR);
                         
                }
                else if (lhlevel == 221) {
                        write(HBMAG HIY"\n��������ϰ�������е���ż��΢΢һ�������͸о����������ȣ�ԴԴ������\n"NOR);
                       
                }
        }
        if( !me->query("quest/Ħ����/luohan")){
		me->set("quest/Ħ����/luohan", 1);
		log_file("quest/Ħ����/luohan",sprintf("%8s%-10s�ɹ��õ�����ʼ�ж��޺���ħ������ʱ�ȼ��ǣ�%s��\n",
			me->name(1),"("+capitalize(me->query("id"))+")", chinese_number(lhlevel )), me);
        }
        return 1;
}
