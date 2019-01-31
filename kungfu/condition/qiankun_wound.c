#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;
int update_condition(object me, int duration)
{
        if (duration < 1) {
                message_vision(HIY"$N终于打通了胸口穴道，内息回复了正常。\n" NOR, me);
                me->set("max_neili",me->query("qiankun/neili"));
                return 0;
        }
        if (!duration) return 0;
        if( !living(me)){
                message_vision(HIR"$N按住胸口，闷哼一声，似乎内息不顺。\n" NOR, me);
        }
        else {
                message_vision(HIR"$N按住胸口，闷哼一声，似乎内息不顺。\n" NOR, me);
        }
        me->apply_condition("qiankun_wound", duration - 1);
        return CND_CONTINUE;
}

string query_type(object me)
{
        return "wound";
}

