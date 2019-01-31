// panix 01/09/14

#include <ansi.h>
void remove_effect(object me,int count);

//毒的列表 copy from yinyun-ziqi qudu
mapping *poi_list = ({
([
"id":		"snake_poison",	// 所中毒的E文名称
"name":		"蛇毒",		// 所中毒的中文名称
"col":		""BLU"",	// 中毒发作的颜色
"con":		"湛蓝之痕",	// 中毒发作的状态
]), 
([
"id":		"xx_poison",
"name":		"星宿掌毒",
"col":		""BLU"",
"con":		"湛蓝之痕",
]),
([
"id":		"xuanmin_poison",
"name":		"玄冥掌毒",
"col":		""HIW"",
"con":		"霜白之痕",
]),
([
"id":		"dsy_poison",
"name": 	"密宗大手印掌毒",
"col":		""CYN"",
"con":		"青色之痕",
]),
([
"id":		"fs_poison",
"name":		"腐尸毒",
"col":		""HIG"",
"con":		"绿色之痕",
]),
([
"id":		"huagu_poison",
"name":		"化骨绵掌剧毒",
"col":		""BLU"",
"con":		"湛蓝之痕",
]),
([
"id":		"man_poison",
"name":		"蔓陀萝花毒",
"col":		""HIB"",
"con":		"黑色之痕",
]),
([
"id":		"qinghua_poison",
"name":		"情花毒",
"col":		""MAG"",
"con":		"紫色之痕",
]),
([
"id":		"qishang_poison",
"name":		"七伤拳毒",
"col":		""HIR"",
"con":		"潮红之痕",
]),
([
"id":		"qzhu_poison",
"name":		"千蛛万毒手毒",
"col":		""HIR"",
"con":		"潮红之痕",
]),
([
"id":		"sl_poison",
"name":		"神龙毒",
"col":		""BLU"",
"con":		"湛蓝之痕",
]),
([
"id":		"sy_poison",
"name":		"大手印掌毒",
"col":		""HIR"",
"con":		"潮红之痕",
]),
([
"id":		"warm_poison",
"name":		"热毒",
"col":		""RED"",
"con":		"殷红之痕",
]),
([
"id":		"hot_poison",
"name":		"火毒",
"col":		""HIR"",
"con":		"潮红之痕",
]),
([
"id":		"cold_poison",
"name":		"寒毒",
"col":		""HIC"",
"con":		"绿青之痕",
]),
([
"id":		"bing_poison",
"name":		"冰魄银针毒",
"col":		""HIB"",
"con":		"湛蓝之痕",
]),
([
"id":		"bt_poison",
"name":		"怪蛇毒",
"col":		""YEL"",
"con":		"泛黄之痕",
]),
([
"id":		"hb_poison",
"name":		"寒冰绵掌毒",
"col":		""HIB"",
"con":		"湛蓝之痕",
]),
});

int exert(object me)
{    
      int improve;
	  if (me->query("yjj/powerup")!="pass") 
		  return notify_fail("你只是听说过易筋经之无相神功，但却并不会使用「无相神功」！\n");
      if ( !me->is_fighting()&&(int)me->query_skill("yijin-jing", 1) < 550)
                return notify_fail("你只能在战斗中使用易筋经「无相神功」！\n");

      if( (int)me->query_skill("yijin-jing", 1) < 450 )
                return notify_fail("你的易筋经内功修为不够，无法使用「无相神功」！\n");
				
	  if( (int)me->query_skill("buddhism", 1) < 200 )
                return notify_fail("你的佛法修为不够，无法使用「无相神功」！\n");

      if (me->query_skill_mapped("force") != "yijin-jing")
                return notify_fail("你所使用的内功不对！\n");

      if( (int)me->query_con() < 60 )
                return notify_fail("你的根骨太低，根本无法使用「无相神功」！\n");
 
      if( (int)me->query("neili") < 5000 )
                return notify_fail("你目前的内力太少了，无法使用「无相神功」！\n");   
      if( (int)me->query_skill("medicine",1) < 120 )
                return notify_fail("你目前的本草术理太少了，无法使用「无相神功」！\n");   
      if( (int)me->query("max_neili") < 10000 )
                return notify_fail("你的内力修为这么差，还想使用「无相神功」？\n");   
                                                                                
      if( me->query_temp("yjj/powerup"))
                return notify_fail("你正在运用「无相神功」！\n");
				
	  improve = (int)me->query_skill("yijin-jing", 1)/10;
	  if ( improve > 60 ) improve = 60 + (improve-60) / 10;
	  me->set_temp("yjj/powerup",improve);
       
      message_vision(HBRED+HIW"\n$N心中默念：若菩萨有我相、人相、众生相、寿者相，即非菩萨。顿觉心无所执，现大自在，易筋经神功全身流转，随心所欲！\n" NOR, me);
      if ((int)me->query_skill("yijin-jing", 1) < 500){
          me->start_busy(random(1));
		  me->start_exert(2,"「无相神功」");
	  }
     // me->set_temp("yjj/powerup", me->query_skill("yijin-jing", 1)/2); 
     // me->add_temp("apply/dodge", me->query_skill("yijin-jing", 1)/6); //dodge,parry 由金刚完成，金刚侧重防御，powerup侧重攻击
      //me->add_temp("apply/parry", me->query_skill("yijin-jing", 1)/6);
      me->add_temp("apply/attack", me->query_skill("yijin-jing", 1)/2);
	  me->add_temp("apply/damage", me->query_skill("yijin-jing", 1)/4);
      me->add("neili", -500);
      message_vision(HBRED+HIY"$N已完全融会贯通易筋经全部行功法诀，什么平庸之极的武功，到了手里，都能化腐朽为神奇！\n" NOR, me);
	  me->add_temp("apply/strength", improve);
	  me->add_temp("apply/constitution", improve/2);
	  me->add_temp("apply/dexerity", improve);
	  me->add("neili", -500);
	     
      call_out("remove_effect", 1, me, improve);
      return 1;
}

void remove_effect(object me,int count)
{
        int improve;
		mapping conditions,my_poison,poison;
 	    string *names,name,poison_name,poison_col,poison_con;
 	    int lvl=0;
	    int i,k;
		if (!me) return;
	    
		poison_name="未知毒";
		poison_col=""HIB"";
		poison_con="无色之痕";
		improve = (int)me->query_temp("yjj/powerup");
	   
        if( !me) return;
        if(me->query_temp("yjj/powerup")) {
            if( count < 1 ){
                me->delete_temp("yjj/powerup");             
                me->add_temp("apply/attack",-me->query_skill("yijin-jing", 1)/2);             
		    	me->add_temp("apply/damage",-me->query_skill("yijin-jing", 1)/4);
		        me->add_temp("apply/strength", -improve);
		        me->add_temp("apply/constitution", -improve/2);
		        me->add_temp("apply/dexerity", -improve);
		       //	me->delete_temp("yjj/powerup");
                message_vision(HIR"\n$N心念滋生，再也难以维持无相无我的大自在状态。\n"NOR, me);    
                return;
            }
            else { 
		        if (me->query_temp("yjj/powerup") 
					//&& me->query("yjj/powerup")
					&&!random(2)) {
	              
					if(mapp(conditions = me->query_conditions_by_type("poison"))){
	                	names = keys(conditions);
						
	                	for(i=0;i<sizeof(conditions);i++){
						    name  = names[i];
							//将毒名与存根对应,并给于标记
							for(k=0;k<sizeof(poi_list);k++) {
	                         	if(poi_list[k]["id"]==name) {
	                         	  poison_name=poi_list[k]["name"];
							      poison_col =poi_list[k]["col"];
							      poison_con =poi_list[k]["con"];
							      break;
								  }
	                        }							
							
							//如果身体内有毒,则开始解毒
	                		if(conditions[names[i]]>0) {
							   message_vision(HIY"$N早已融会贯通易筋经的全部行功法诀，金色皮肤下"+poison_col+poison_con+HIY+"时隐时现,却是易筋经正将体内"+poison_col+poison_name+HIY+"的毒质逐步消解！\n"NOR,me);
                               me->add_condition(name,-random((int)me->query_condition(name)));
							}
							else {
							   message_vision(HIY"$N早已融会贯通易筋经的全部行功法诀，金色皮肤下"+poison_col+poison_con+HIY+"一闪而没,原来易筋经已将体内"+poison_col+poison_name+HIY+"的毒质彻底消解！\n"NOR,me);
                               me->clear_condition(name);
							}
	                	} //将所有毒素都清除。
	                }
			    }
                call_out("remove_effect", 1, me,count -1);
                return;
            }
        }
}
string exert_name(){ return HIW"无相神功"NOR; }

int help(object me)
{
        write(HIY"\n易筋经之「无相神功」："NOR"\n");
        write(@HELP
        《易筋经》实是武学中至高无上的宝典，只是修习的法门甚为不易，须
        得勘破“我相、人相”。心中不存修习武功之念，才能修至大成境界，
        一旦融会贯通易筋经全部行功法诀，什么平庸之极的武功，到了手里，
        都能化腐朽为神奇，而且功行全身，能够消解百毒。
        
		要求：
			易筋经等级 450 以上；
			禅宗心法等级 200 ；
			根骨 60 以上；
			最大内力 10000 以上；
			内力 5000 以上。
HELP
        );
        return 1;
}
