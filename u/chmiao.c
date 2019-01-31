// Room: /d/city/chmiao.c
// Modify by Lklv 2001.10.16

#include <ansi.h>

inherit ROOM;
void create()
{
        set("short", "������");
        set("long", @LONG
�������ݳǱ��ĳ���������ƽ�����ϡ�٣���������ڡ�����ڻ�����
���ʱ�򣬲Ż���Щ������з���һ��������������������˻ҳ���ǽ��
���и���֩��������ֻ֩�����ĵض������档
LONG    );
        set("exits", ([
                "east" : __DIR__"beidajie1",
               "up" : __DIR__"qipaishi",
                "northwest" : "/d/wizard/guest_room",
        ]));
        set("no_fight", 1);
        set("no_sleep_room", 1);
        set("objects", ([
                __DIR__"npc/ymonk" : 1,
                __DIR__"obj/box" : 1
        ]));
        setup();
        "/clone/board/wizto_b"->foo();
}

void init()
{
        object env, link_ob, obj;
        
        object me = this_player();
        
        env = environment(me);

        if (me->query("qiankun/qi") && me->query("qiankun/neili")) {
                 me->set("max_qi",me->query("qiankun/qi"));
                 me->set("max_neili",me->query("qiankun/neili"));
                 me->delete("qiankun/qi");
                 me->delete("qiankun/neili");
        }

        me->delete_temp("die_record");

        //�Խ�ɽׯϴ��״̬�ָ�
        if(me->query("no_pk_recover")){
            tell_object(me,BLINK + HIC"���뿪���Խ�ɽׯ��ϵͳ�Զ��ָ�������ϴ��״̬��\n"NOR);
            me->set("no_pk",me->query("no_pk_recover"));
            me->delete("no_pk_recover");
        }
        me->clear_condition("sjsz_time");
        add_action("action", ({
                "dazuo",
                "du",
                "exercise",
                "lian",
                "practice",
                "respirate",
                "study",
                "tuna"
        }));


if(me->query_temp("death_relife"))
{
        
        me->delete_temp("death_relife");
//��ֹ����ʱ�������ݸ��������嵼��ѭ�����
 

        link_ob = me->query_temp("link_ob");
        write("��������ģ�塣��׼��������\n\n");
	obj = new(link_ob->query("body"));

//����ÿһ������ɹ���׷��
//������Ȼ����ȷ����ˣ������ڴ���uid��ʱ����˵����⡣
//�Ҳ����ֲᰡ������������Ҫ�����ԭʼ��uid���ݸ��µ�����obj����mldgd

        seteuid(link_ob->query("id"));
        export_uid(obj);
	 export_uid(link_ob);
        seteuid(link_ob->query("id"));
	 obj->set_name(link_ob->query("name"), ({ link_ob->query("id")}));

       write("���������塣��׼��������\n\n");


        if (!obj){
write("������ģ����󡣡���\n\n");
                return 0;}
        // Save the data and exec the player to his/her link object.
        //me->update_age();
          me->setup();
write("�����������ݡ�����ϡ�\n\n");

        me->save();
        write("����������ݡ�����ϡ�\n\n");

        exec(link_ob, me);

        write("׼��д���µ��������ݡ�������ϡ�\n\n");
       
         destruct(me);
       
        write("�ݻپɵ����������������ϡ�\n\n");
       

        // Restore new body and exec to it via enter_world in LOGIN_D
        obj->restore();

        write("������������С�������ϡ�\n\n");

        LOGIN_D->enter_world(link_ob, obj, 1);

        write("���������ϡ�\n\n");
        obj->move(env);
        obj->write_prompt();



}

}

int action()
{
        write("���޷���������������\n");
        return 1;
}
int valid_leave(object me, string dir)
 {
     mapping exits = query("exits");
     if (!load_object(exits[dir])->query("xyjob") 
     && me->query_temp("xyjob"))
             return notify_fail("����ս�½������㻹�Ǳ�ȥ�����ˣ���\n");
     return ::valid_leave(me, dir);
 }
