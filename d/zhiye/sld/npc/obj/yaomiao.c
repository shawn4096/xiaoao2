// yaomiao.c

#include <ansi.h>

inherit ITEM;

int gf=0;
 
void create()
{
        set_name(HIG "ҩ��" NOR, ({"yao miao","miao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long",
                "����һ�꾫Ʒҩ�磬��Ҫ������ˮ(jiao)���������׸�����ҩ�����ǽ���ʹ�����");
                set("unit", "��");
                set("no_get",1);
                set("5type","��");
                set("8type","Ǭ");
                set("stime",0);
                set("location",1);
        }
}

void init()
{
        add_action("do_jiao","jiao");
                        
}

int do_jiao(string arg)
{
        object ob;
        object me=this_player();
     
        if(gf==0)
        {
                gf=1;
                call_out("grow", 10,me); 
        }
        if(!arg || !objectp(ob=present(arg, environment(me))))
                return notify_fail("����û�磬��Ҫ��ʲô��\n");
        if (ob->query("owner")!=me->query("id"))
			return notify_fail("�����粻����ģ��㲻��ҩ�ԣ��޷���ˮ��\n");
		
		if (!me->query_temp("sld/zhongyao/yumiao"))
			return notify_fail("��������ô������\n");
		if((uptime()-ob->query("jtime"))>30)
        {
                call_out("destructing", 1, ob); 
				me->delete_temp("sld/zhongyao");
				//environment(this_object())->delete("zhongyao");
                return notify_fail("���Ѿ�һ���û��ˮ��ҩ������ˡ�\n");
        }
		else if((uptime()-ob->query("jtime"))<10)
        {
                return notify_fail("��ս���ˮ�ˣ��Ȼ���ٽ��ɡ�\n");
        }

        ob->set("jtime",uptime());
        message_vision("$N����һưˮ��ҩ���ֳ�����Щ��\n",me);
        return 1;
}
void destructing(object ob)
{
        if(ob)
          destruct(ob);
}


void grow(object me)
{
        int times;
        object obj;
        object ob=this_object();
		if (!me) return;
	
        times=uptime()-query("stime");
        if(times>=120)
        {

                if(!objectp(obj=new(__DIR__"yaocao")))
                {
                        call_out("grow", 10,me);
                } 
                else
                {
						message_vision(HIM"�����ڿ콽ˮ�����£�ҩ��������׳�ɳ����Ѿ���Ϊ�����ҩ��!\n"NOR,me);
						message_vision(HIY"��ϲ$N��"HIM+ob->query("8type")+HIG+ob->query("5type")+HIY"ҩ�Ե�ҩ�������ɹ���!\n"NOR,me);

                        obj->set("5type",query("5type"));
                        obj->set("8type",query("8type"));
                        obj->set("long",obj->query("long")+query("8type")+query("5type")+"�ԡ�\n");
						obj->set("owner",me->query("id"));
						obj->set("long",obj->query("long")+"����һ����"+me->query("name")+"����������ҩ�磡\n");
                        obj->move(environment(this_object()));
                        call_out("destructing", 1, ob); 
						me->set_temp("sld/zhongyao/miaook",1);
						me->improve_skill("yaozhi",me->query_int());
						return;
                }
        }
        else if(times>=60)
        {
				message_vision(YEL"�����ڿ콽ˮ�����£�ҩ��������׳�ɳ����Ѿ���Ϊ��Ƶ�ҩ��!\n"NOR,me);
				me->improve_skill("yaozhi",me->query_int());
                set("name",YEL"��Ƶ�ҩ��"NOR);
                call_out("grow", 60,me);   
        }
        else
        {
			message_vision(HIG"�����ڿ콽ˮ�����£�ҩ��������׳�ɳ����Ѿ���Ϊ�����ҩ��!\n"NOR,me);
			me->improve_skill("yaozhi",me->query_int());
            set("name",HIG"�����ҩ��"NOR);
            call_out("grow", 30,me);   
        }
}