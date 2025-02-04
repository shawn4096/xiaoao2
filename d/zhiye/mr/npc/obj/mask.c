// mask.c
//

inherit ITEM;

void create()
{
        set_name("面具", ({ "mian ju", "mask" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                set("long", "这似乎是一个由人皮制成的面具。\n");
               set("unique", 1);
                set("value", 10000);
        }
        setup();
}

void init()
{
        add_action("do_pretend", "yirong");
}

int do_pretend(string arg)
{
        object who;
        object me;
        string *mask;
        string pshort;

        if (! arg)
                return notify_fail("你想易容成谁？\n");
       
        me = this_player();
		if (me->query("combat_exp")<10000000)
                return notify_fail("你经验值太低，功力不够，很难易容成别人。\n");
        if (arg == "none" || arg == "cancel")
        {
                if (! query_temp("owner"))
                        return notify_fail("你现在并没有使用面具。\n");

                me->delete_temp("apply/name");
                me->delete_temp("apply/short");
                me->delete_temp("apply/long");
                message_vision("$N从脸上取下了一个人皮面具。\n", me);
                return 1;
        }


        if (! objectp(who = present(arg, environment(me))) || 
            ! living(who))
                return notify_fail("你想易容成谁？\n");

        if (wizardp(who))
                return notify_fail("你无法易容成巫师。\n");

        if (sizeof(mask = who->query_temp("apply/short")))
                pshort = mask[sizeof(mask) - 1];
        else
                pshort = who->short(1);

        write("你开始将自己易容成" + who->name() + "。\n");
        me->set_temp("apply/name", ({ who->name() }));
        me->set_temp("apply/short", ({ pshort }));
        me->set_temp("apply/long", ({ who->long() }));
        set_temp("owner", me);
        return 1;
}

int move(mixed dest)
{
        object me;

        if (me = query_temp("owner"))
        {
                me->delete_temp("apply/name");
                me->delete_temp("apply/short");
                me->delete_temp("apply/long");
                delete_temp("owner");
        }

        return ::move(dest);
}



