// 氤氲紫气 太极功 PFM
// by sohu@xojh 2014.1

#include <ansi.h>

string exert_name(){ return HBMAG+HIW"太极神功"NOR; }

int check_fight(object me);
int exert(object me)
{
		object weapon;
		int skill;
  		skill=me->query_skill("yinyun-ziqi",1);
	    
        if (!me->query("quest/wd/yyzq/taiji/pass"))
        		return notify_fail("你尚未参悟透「太极」真意，施展不出太极劲。\n");
		
        if( !me->is_fighting() || 
			!living(me))
                return notify_fail("「太极」只能在战斗中的使用。\n");
        if( me->query_temp("yyzq/taiji")) 
                return notify_fail("「太极」之意绵绵不绝，你已经在发挥它的威力了。\n");  
        if( (int)me->query("max_neili") < 15000 )
                return notify_fail("你的最大内力修为太弱，发挥不出「太极」的优势。\n");                
        if( (int)me->query("neili", 1) < 500 )
                return notify_fail("你现在真气不够，发挥不出「太极」的威力。\n");
        if( (int)me->query_skill("yinyun-ziqi", 1) < 500 )
                return notify_fail("你的氤氲紫气等级不够高，发挥不出「太极」的威力。\n");
        if( (int)me->query_skill("taiji-jian", 1) < 500 )
                return notify_fail("你的太极剑法不够娴熟，还不能领会「太极」之诀窍。\n");
        if( (int)me->query_skill("taiji-quan", 1) < 500 )
               	return notify_fail("你尚未完全参悟太极拳，无法再使用「太极」诀窍了。\n");
		if((int)me->query_skill("taoism", 1) < 200 )
                return notify_fail("你对道学心法的领悟不够，发挥不出「太极」那圆转不断的真意。\n");
        if( me->query_skill_mapped("force") != "yinyun-ziqi")
                return notify_fail("你的内功不对，根本不能发挥出「太极」的优势。\n");                                                                                     
        if( userp(me) 
           &&( me->query_skill_mapped("parry") != "taiji-quan"&& me->query_skill_mapped("parry") != "taiji-jian") )
                return notify_fail("「太极」诀窍必须在用太极拳或太极剑激发招架的情况下才能使用。\n");
        if( me->query_skill_prepared("cuff") != "taiji-quan"
           || me->query_skill_mapped("cuff") != "taiji-quan")
                return notify_fail("你必须懂得太极拳，才能施展「太极」。\n");  
        if( me->query_skill_mapped("sword") != "taiji-jian" )
                return notify_fail("你必须懂得太极剑法，才能施展「太极」。\n"); 
              
        if( objectp(weapon = me->query_temp("weapon")) ){
        	    if( weapon->query("skill_type") != "sword" )
                	return notify_fail("你必须使用剑才能运用「太极」施展出太极剑意！\n");           
              
         message_vision(HIC"\n$P缓缓移动，一手持剑，一手画了个剑指，两足分开平行，接着两臂慢慢提起至胸前，\n但见$P剑出剑回，每一招都含着太极式的阴阳变化，精微奥妙！\n",me);
         tell_object(me, CYN"\n你默运太极神功，将自己和剑与万物合一，将太极"RED"「剑意」"CYN"发挥得淋漓尽致！\n"NOR);
        }
        else {                  
        	message_vision(HIC"\n$P缓缓移动，双手下垂，手背向外，手指微舒，两足分开平行，接着两臂慢慢提起至胸前，左臂半环，\n"
+"掌与面对成阴掌，右掌翻过成阳掌，但见$P双手圆转，每一招都含着太极式的阴阳变化，精微奥妙！\n",me);
        	tell_object(me, HIW"\n你默运神功，双手自然挥动，与万物合一，将「太极」"RED"「拳意」"HIW"发挥得淋漓尽致！\n"NOR);
        }
		
		me->set_temp("yyzq/taijiing",1);//设置停止标记
		
        //if (me->query_skill("yinyun-ziqi",1) < 450 ) me->start_busy(1+random(2)); //中飞取消busy
		if (skill > 549 ) //大飞增强防御
		{
			
			//这里采用通用buff函数 
		//参数：目标 buff名 buff值 buff时间 临时标记,散功描述,战斗停止标记
			
		 //CHAR_D->addbuff(me,"armor",skill/3,3,"yyzq/armor",0,1); 
		// CHAR_D->addbuff(me,"defense",skill/3,3,"yyzq/defense",0,1);
		// CHAR_D->addbuff(me,"parry",skill/3,3,"yyzq/parry",0,1);
		// CHAR_D->addbuff(me,"dodge",skill/3,3,"yyzq/dodge",0,1);
			 
			
			/*me->set_temp("apply/armor",0);
			me->set_temp("apply/defense",0);
            me->set_temp("apply/parry",0);
			me->set_temp("apply/dodge",0);*/
			
			me->add_temp("apply/armor",skill/3);
			me->add_temp("apply/defense",skill/3);
            me->add_temp("apply/parry",skill/3);
			me->add_temp("apply/dodge",skill/3);
			me->set_temp("yyzq/dafei",skill);
			
			
			
			//me->add_temp("apply/strength",(int)me->query_skill("yinyuan-ziqi",1)/10);
		}
		
      
		me->set_temp("yyzq/taiji",skill);
        check_fight(me);
        return 1;
}

string check_force(object ob)
{
	string force;
	
	if(!stringp(force = ob->query_skill_mapped("force")))
       		force = "内功";
        
        switch(force){
        	case "yinyun-ziqi": break;
        	case "huntian-qigong":
        	case "hamagong":
        	case "longxiang-boruo": force = "钻翻"; break;
        	case "huagong-dafa":
        	case "guiyuan-tunafa":
        	case "dulong-dafa": force = "螺旋"; break;
        	case "yijin-jing":
        	case "bihai-chaoshen":
        	case "qiantian-yiyang":
        	case "kurong-changong": force = "软手"; break;        	
        	case "shenyuan-gong":
        	case "zixia-gong":
        	case "shenghuo-shengong": force = "开合"; break;        	
        	case "lingji-zhuang":
        	case "yunu-xinjing":
        	case "shenzhao-jing": force = "静恒"; break;
        	default: force = "虚灵"; break;
        } 
        return force;
}
        
int check_fight(object me)
{    
	object ob, weapon;
	string force;
	int skill;
	if (!me) return 0;
	
	skill=me->query_skill("yinyun-ziqi",1);
	
	if( !me || !me->query_temp("yyzq/taiji") ) return 0;
	weapon = me->query_temp("weapon");
	    if (!me->is_fighting() || me->query("neili") <= 100 || !living(me) || !me->query_temp("yyzq/taijiing"))
	    {
			
			if( !weapon )  	message_vision(CYN "\n$N使到「收势」而合太极，两前臂内旋前伸，左右分开，臂微屈，腕与肩平，两手心徐徐下落，神定气闲的站在当地。\n\n"NOR, me);
		    else 	message_vision(CYN "\n$N将剑招中止，双手抱剑于胸前，徐徐下落，神定气闲的站在当地。\n\n"NOR, me);
			message_vision(HIW"$N将太极神功缓缓收功，含胸而立，静若处子。\n"NOR,me);
			if (me->query_temp("yyzq/dafei")) 
		    {
				skill=me->query_temp("yyzq/dafei");
				// me->set_temp("apply/armor",0);
              //  me->set_temp("apply/parry",0);
		    //	me->set_temp("apply/dodge",0);
			//	me->set_temp("apply/defense",0);	
				
			    me->add_temp("apply/armor",-skill/3);
                me->add_temp("apply/parry",-skill/3);
		    	me->add_temp("apply/dodge",-skill/3);
				me->add_temp("apply/defense",-skill/3);	
				
				me->delete_temp("yyzq/dafei");
				
				
		     }
			 //取消太极系列super设置
				me->delete_temp("tjq/super_hit");
				me->delete_temp("tjj/super_hit");
				
			 me->delete_temp("yyzq/taiji");
			 me->delete_temp("yyzq/taijiing");
			return 1;
		}
		else
		{
			if( weapon ){
        	if( weapon->query("skill_type") != "sword" ){
        		write(HIY"你手中非剑，太极剑意顿时便不能连通了！\n"NOR);
        		me->delete_temp("yyzq/taijiing");
				
        	}
        	else if( me->query_skill_mapped("sword") != "taiji-jian" ){
                	message_vision(CYN"$N突然将太极剑法一收，换一一种剑法出来！太极剑意顿失!\n"NOR, me);
                	me->delete_temp("yyzq/taijiing");
					
                }
                
            else if( (int)me->query_skill("taiji-jian", 1) < 500 ){
                	write(HIY"你的太极剑法不够娴熟，领会不了「太极」之诀窍！\n"NOR);
                	me->delete_temp("yyzq/taijiing");
					
        	}
			else if( me->query_skill_mapped("parry") != "taiji-jian" )
			{
				    message_vision(CYN"$N突然将太极剑法一收，换一一种剑法出来！太极剑意顿失!\n"NOR, me);
                	me->delete_temp("yyzq/taijiing");				
			}
            else me->set_temp("tjj/super_hit",1);
        		//me->map_skill("parry", "taiji-jian");
			
			
        }        
        else {
        	if ( me->query_skill_mapped("cuff") != "taiji-quan" 
        		|| me->query_skill_prepared("cuff") != "taiji-quan" ){
                	message_vision(HIY"$N使完一式太极拳，突然变招，竟然是完全不同的招数！太极浑圆之意顿失。\n"NOR,me);
                	me->delete_temp("yyzq/taijiing");
                	me->start_busy(1);
        	}
            else if( me->query_skill_mapped("parry") != "taiji-quan" )
			{
				message_vision(HIY"$N使完一式太极拳，突然变招，竟然是完全不同的招数！太极浑圆之意顿失。\n"NOR,me);
                	me->delete_temp("yyzq/taijiing");
                	me->start_busy(1);				
			}			
       		else{      
       			if( me->query_skill("taiji-quan", 1) > 450
       			&& objectp(ob = me->select_opponent()) 
       			&& random(me->query_int()) > ob->query_int()
       			&& !me->query_temp("tjq/"+ob->query("id"))
       			&& stringp(force = check_force(ob)) 
       			&& force != "yinyun-ziqi"){
        			tell_object(me, HIC"你这一细心观察，发现了"+ob->name()+"所用内功的虚实，手腕一转，运出六合"+force+"劲来！\n"NOR);
        			me->set("env/六合劲", force);
        			me->set_temp("tjq/"+ob->query("id"), random(me->query_int(1))+1);
				me->set_temp("tjq/super_hit",1);
        		}        		
        	}
			
        }
		call_out("check_fight",1, me);	
         return 0;		
		}        
       	return 1;
}       

int help(object me)
{
	write(HIM"\n氤氲紫气"HIW"「太极神功」："NOR"\n");
	write(@HELP
	太极之意，虽变化万端，而理为一贯。由招熟
	而渐悟懂劲由懂劲而阶及神明。然非用力日久，
	不能豁然贯通焉。基本上所有太极拳剑绝招都
	须以此来配合。每见数年纯功，不能运化者，
	率皆自为人制，双重之病未悟而；循序加力须
	等级三百五十以后，阴阳相济，方为懂劲。懂
	劲后，方能愈练愈精。太极功乃是张真人晚年
	将自己一身武学融会贯通，所悟而得，属于本
	门最高武学，通过考验后，需向张真人请教。
	注意：太极内劲乃是张真人晚年所创，重意不
	重力，如长江大河，绵绵不绝。太极内功定位
	成本江湖中绝顶内功设置，难度系数较高，但
	开了后，威力也值得期待，切忌太极功重在厚
	积薄发，550后威力方的彰显。
	
	使用指令：yun taiji

要求：
	太极拳法等级 500 以上；
	太极剑法等级 500 以上)
	氤氲紫气等级 500 以上；
	道学心法等级 200 以上；
	最大内力 15000 以上；
	当前内力 1000 以上。
HELP
	);
	return 1;
}
