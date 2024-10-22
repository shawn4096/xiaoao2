
// CLOTH_D
// by augx@sj  10/16/2001

#include <ansi.h>
#include <armor.h>

int armor_cut(object me, object victim, object weapon, int damage)
{
        mapping mp;
        object * armors;
        int i,dur;
        
        if( !mapp(mp = victim->query_temp("armor")) ) return 0;
        
        armors = values(mp);
        for(i=0;i<sizeof(armors);i++) {
                if( !objectp(armors[i]) ) continue;
                        
      if( (int)armors[i]->query("dur") > 0&&!me->query("vip_as")&& !victim->query("vip_as")) {
                        if(weapon) dur = (int)weapon->query("sharpness"); else dur=1;
                        if(dur<1) dur = 1;
                        
                        armors[i]->add("dur", -dur);
                        if( mapp(armors[i]->query("armor_mp")) )
                                armors[i]->add("armor_mp/dur", -dur);
                        if( (int)armors[i]->query("dur") <= 0 ) {
                                message_vision(HIW"$N身上的"+armors[i]->name()+HIW"寿命已到，终于裂为碎片！\n"NOR,victim);
                                armors[i]->broken("破碎的");
                                return 1;
                        }
                }
        }
        
        return 0;
}

int armor_vs_poison(object me, int poison,string p)
{
        int antipoison,i;
        
        if(objectp(me->query_temp("armor/neck")) && me->query_temp("armor/neck")->id("hate snake's zhu") && p=="snake_poison" )
                return poison+1;
        if( (antipoison = (int)me->query_temp("apply/antipoison")) <= 0 ) return 0;
        if( antipoison > 90 ) antipoison = 90;
        if( random(100) < antipoison ) return poison;
        
        i = random(antipoison*3/2);
        if(i>90) i=90;
        return (int)(poison * i/100);
}
