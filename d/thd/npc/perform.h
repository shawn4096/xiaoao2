int ask_shenjian()
{
        object ob = this_player();
        int perform,time;
        
        if (ob->query("family/family_name") != "�һ���") {
                command("say �����������������");
                return 1;
        }
		if (!ob->query("quest/thd/dichuan"))
		{
			command("say ����Ȼ�������е��ӣ���Ϊ�һ�������ʲô�ȣ�\n");
			command("say �Ҷ�а���£��������������أ��ǵմ����Ӳ�����\n");
			return 1;
		}
        //perform = ob->query("thd/perform");
        if (ob->query("thd/wuji/luoying")) {
                command("say �㲻���Ѿ�ѧ������");
                return 1;
        }
        if (ob->query("age") < 14) {
                command("say Ҫʹ�������ľ�����Ҫ�������㻹�ǵȳ���Щ��˵�ɡ�");
                return 1;
        }
/*   // ��Ӣ�Ƶ�auto��Ů�����ã�
        if (ob->query("gender") == "����" && ob->query("age") < 40) {
                command("say ���б�����Ҳ���Խ������㣬������Ͳ������������õ�;����");
                return 1;
        }
*/
        if (ob->query_skill("luoying-zhang",1) < 200) {
                command("say Ҫʹ�������ľ�����Ҫ�����������㻹�Ƕ���ϰ��ϰ����Ӣ���ơ���˵�ɡ�");
                return 1;
        }
		time=time() - (int)ob->query("quest/shenjian/time");
       	if (ob->query("quest/shenjian/time") && time<86400)		
   		{
				command("say С�ѻ���ȥ��Ϣһ�°ɡ�");
				return 1;
		}
				 
		if (random(ob->query("kar"))<26)
		 {
                command("sigh "+ob->query("id"));
				command("say Ҫʹ�á��һ�Ӱ����񽣡������ľ���һ�����������㻹���´���˵�ɡ�\n");
				ob->set("quest/shenjian/time",time());
                return 1;
		 }
		  write("��ҩʦ˵�������Ȼ���һ����ĵ��ӣ��Ҿͽ���һ�С��һ�Ӱ����񽣡��ɣ�\n");
          write("��ҩʦϸ�ĵ����㽲����һ�У�������ѧ���ˡ�\n");
          //perform |= 2;
          ob->set("thd/wuji/luoying",1);
		  return 1;
  }

int ask_yuxiao()
{
        object ob = this_player();
        int perform,time;
        
        if (ob->query("family/family_name") != "�һ���") {
                command("say �����������������");
                return 1;
        }
        //perform = ob->query("thd/perform");
		if (!ob->query("quest/thd/dichuan"))
		{
			command("say ����Ȼ�������е��ӣ���Ϊ�һ�������ʲô�ȣ�\n");
			command("say �Ҷ�а���£��������������أ��ǵմ����Ӳ�����\n");
			return 1;
		}
        if (ob->query("thd/wuji/yuxiao")) {
                command("say �㲻���Ѿ�ѧ������");
                return 1;
        }
        if (ob->query("age") < 14) {
                command("say Ҫʹ�������ľ�����Ҫ�������㻹�ǵȳ���Щ��˵�ɡ�");
                return 1;
        }
/*
        if (ob->query("gender") == "����" && ob->query("age") < 40) {
                command("say ���б�����Ҳ���Խ������㣬������Ͳ������������õ�;����");
                return 1;
        }
*/ 
	    if (ob->query_skill("yuxiao-jian",1) < 200) {
                command("say Ҫʹ�������ľ�����Ҫ����Ľ������㻹�Ƕ���ϰ��ϰ�����｣������˵�ɡ�");
                return 1;
        }
		time=time() - (int)ob->query("quest/yuxiao/time");
        if(ob->query("quest/yuxiao/time") && time<86400)		
   		{
				command("say С�ѻ���ȥ��Ϣһ�°ɡ�");
				return 1;
		}
	   
		if (random(ob->query("kar"))<27)
		 {
                command("sigh "+ob->query("id"));
				command("say Ҫʹ�á��̺���������������ľ���һ�����������㻹���´���˵�ɡ�\n");
				ob->set("quest/yuxiao/time",time());
                return 1;
		 }
		
        write("��ҩʦ˵�������Ȼ���һ����ĵ��ӣ��Ҿͽ���һ�С��̺�����������ɣ�\n");
        write("��ҩʦϸ�ĵ����㽲����һ�У�������ѧ���ˡ�\n");
       // perform |= 1;
        ob->set("thd/wuji/yuxiao",1);
        return 1;
}

int ask_kuangfeng()
{
        object ob = this_player();
        int perform,time;
        
        if (ob->query("family/family_name") != "�һ���") {
                command("say " +  RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
                return 1;
        }
       // perform = ob->query("thd/perform");
        if (ob->query("thd/wuji/kuangfeng")) {
                command("say �㲻���Ѿ�ѧ������");
                return 1;
        }
        if (ob->query("age") < 14) {
                command("say Ҫʹ�������ľ�����Ҫ�������㻹�ǵȳ���Щ��˵�ɡ�");
                return 1;
        }
/*
        if (ob->query("gender") == "����" && ob->query("age") < 40) {
                command("say ���б�����Ҳ���Խ������㣬������Ͳ������������õ�;����");
                return 1;
        }
*/
        if (ob->query_skill("luoying-zhang",1) < 100 && ob->query_skill("xuanfeng-tui",1) < 100) {
                command("say Ҫʹ�������ľ�����Ҫ������Ʒ����ȷ����㻹�Ƕ���ϰ��ϰ����Ӣ���ơ��͡�����ɨҶ�ȡ���˵�ɡ�");
                return 1;
        }
	/*	if( time()-ob->query("quest/kuangfeng/time")<86400)		
   		{
				command("say ��̫�ڿ��ˣ�С�ѻ���ȥ��Ϣһ�°ɡ�");
				return 1;
		}
	   
		 if (ob->query("kar")<20)
		 {
                command("sigh "+ob->query("id"));
				command("say Ҫʹ�á��������������ľ���һ�����������㻹���´���˵�ɡ�\n");
				ob->set("quest/kuangfeng/time",time());
                return 1;
		 }*/
        write("��ҩʦ˵�������Ȼ���һ����ĵ��ӣ��Ҿͽ���һ���ҵĿ��ҹ��򡰿��������ɣ�\n");
        write("��ҩʦϸ�ĵ����㽲����һ�У�������ѧ���ˡ�\n");
        //perform |= 4;
        ob->set("thd/wuji/kuangfeng",1);
        return 1;
}

int ask_lingxi()
{
        object ob = this_player();
        int perform,time;
        
        if (ob->query("family/family_name") != "�һ���") {
                command("say " +  RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
                return 1;
        }
        //perform = ob->query("thd/perform");
        if (ob->query("thd/wuji/lingxi")) {
                command("say �㲻���Ѿ�ѧ������");
                return 1;
        }
        if (ob->query("age") < 14) {
                command("say Ҫʹ�������ľ�����Ҫ�������㻹�ǵȳ���Щ��˵�ɡ�");
                return 1;
        }
		if (!ob->query("quest/thd/dichuan"))
		{
			command("say ����Ȼ�������е��ӣ���Ϊ�һ�������ʲô�ȣ�\n");
			command("say �Ҷ�а���£��������������أ��ǵմ����Ӳ�����\n");
			return 1;
		}
/*
        if (ob->query("gender") == "����" && ob->query("age") < 40) {
                command("say ���б�����Ҳ���Խ������㣬������Ͳ������������õ�;����");
                return 1;
        }
*/
        if (ob->query_skill("tanzhi-shentong",1) < 200) {
                command("say Ҫʹ�������ľ�����Ҫ��ǿ��ָ�����㻹�Ƕ���ϰ��ϰ����ָ��ͨ����˵�ɡ�");
                return 1;
        }
		time=time() - (int)ob->query("quest/lingxi/time");
        if(ob->query("quest/lingxi/time") && time<86400)		
   		{
				command("say С�ѻ���ȥ��Ϣһ�°ɡ�");
				return 1;
		}
	   
		if (random(ob->query("kar"))<26)
		 {
                command("sigh "+ob->query("id"));
				command("say Ҫʹ�á���Ϭһָ�������ľ���һ�����������㻹���´���˵�ɡ�\n");
				ob->set("quest/lingxi/time",time());
                return 1;
		 }
        write("��ҩʦ˵�������Ȼ���һ����ĵ��ӣ��Ҿͽ��㡰��ָ��ͨ���ľ��С���Ϭһָ���ɣ�\n");
        write("��ҩʦϸ�ĵ����㽲����һ�У�������ѧ���ˡ�\n");
        //perform |= 8;
        ob->set("thd/wuji/lingxi",1);
        return 1;
}

int ask_huayu()
{
        object ob = this_player();
        int perform,time;
        
        if (ob->query("family/family_name") != "�һ���") {
                command("say " +  RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
                return 1;
        }
       // perform = ob->query("thd/perform");
        if (ob->query("thd/wuji/huayu")) {
                command("say �㲻���Ѿ�ѧ������");
                return 1;
        }
        if (ob->query("age") < 14) {
                command("say Ҫʹ�������ľ�����Ҫ�������㻹�ǵȳ���Щ��˵�ɡ�");
                return 1;
        }
		if (!ob->query("quest/thd/dichuan"))
		{
			command("say ����Ȼ�������е��ӣ���Ϊ�һ�������ʲô�ȣ�\n");
			command("say �Ҷ�а���£��������������أ��ǵմ����Ӳ�����\n");
			return 1;
		}
/*
        if (ob->query("gender") == "����" && ob->query("age") < 40) {
                command("say ���б�����Ҳ���Խ������㣬������Ͳ������������õ�;����");
                return 1;
        }
*/
        if (ob->query_skill("tanzhi-shentong",1) < 120) {
                command("say Ҫʹ�������ľ�����Ҫ��ǿ��ָ�����㻹�Ƕ���ϰ��ϰ����ָ��ͨ����˵�ɡ�");
                return 1;
        }
		time=time() - ob->query("thd/huayu/time");
		if(ob->query("thd/huayu/time") && time<86400)		
   		{
				command("say С�ѻ���ȥ��Ϣһ�°ɡ�");
				return 1;
		}
	   
		if (random(ob->query("kar"))<15)
		 {
                command("sigh "+ob->query("id"));
				command("say Ҫʹ�á����컨�ꡰ�����ľ���һ�����������㻹���´���˵�ɡ�\n");
				ob->set("quest/huayu/time",time());
                return 1;
		 }
        write("��ҩʦ˵�������Ȼ���һ����ĵ��ӣ��Ҿͽ��㡰��ָ��ͨ���ľ��С����컨�ꡱ�ɣ�\n");
        write("��ҩʦϸ�ĵ����㽲����һ�У�������ѧ���ˡ�\n");
        //perform |= 16;
        ob->set("thd/wuji/huayu",1);
        return 1;
}
int ask_lhs()
{
        object ob = this_player();
        int perform,time;
        
        if (ob->query("family/family_name") != "�һ���") {
                command("say �������ǼҴ���ѧ�������ʲô��");
                return 1;
        }
       // perform = ob->query("thd/perform");
        if (ob->query("thd/wuji/lhs")) {
                command("say �㲻���Ѿ�ѧ������");
                return 1;
        }
        if (ob->query("age") < 14) {
                command("say Ҫʹ�������ľ�����Ҫ�������㻹�ǵȳ���Щ��˵�ɡ�");
                return 1;
        }
		if (!ob->query("quest/thd/dichuan"))
		{
			command("say ����Ȼ�������е��ӣ���Ϊ�һ�������ʲô�ȣ�\n");
			command("say �Ҷ�а���£��������������أ��ǵմ����Ӳ�����\n");
			return 1;
		}
        if (!ob->query("thd/finish")) {
                command("say ���б�����Ҳ���Խ������㣬������Ͳ������������õ�;����");
				command("say �ҵľ����澭����������ͽ��͵���ˣ�˭�ܰ��Ұ���������ͽץ������ ");
                return 1;
        }

        if (ob->query_skill("lanhua-shou",1) < 200) {
                command("say Ҫʹ�������ľ�����Ҫ������ַ����㻹�Ƕ���ϰ��ϰ�������֡���˵�ɡ�");
                return 1;
        }
		time=time() - (int)ob->query("quest/lhs/time");
		if(ob->query("quest/lhs/time") && time<86400)		
   		{
				command("say С�ѻ���ȥ��Ϣһ�°ɡ�");
				return 1;
		}
	   
		 if (random(ob->query("kar"))<27)
		 {
                command("sigh "+ob->query("id"));
				command("say Ҫʹ�á�������Ѩ�������ľ���һ�����������㻹���´���˵�ɡ�\n");
				ob->set("quest/lhs/time",time());
                return 1;
		 }
        write("��ҩʦ˵�������Ȼ���һ����ĵ��ӣ��Ҿͽ���һ�С�������Ѩ���ɣ�\n");
        write("��ҩʦϸ�ĵ����㽲����һ�У�������ѧ���ˡ�\n");
       // perform |= 32;
        ob->set("thd/wuji/lhs",1);
	return 1;
}
//�����ں�
int ask_ronghe()
{
        int i,j,time;
		object ob = this_player();
        
        
        if (ob->query("family/family_name") != "�һ���"||ob->query("family/master_name")!="��ҩʦ") {
                command("say �������ǼҴ���ѧ�������ʲô��");
                return 1;
        }
		if (!ob->query("quest/thd/dichuan"))
		{
			command("say ����Ȼ�������е��ӣ���Ϊ�һ�������ʲô�ȣ�\n");
			command("say �Ҷ�а���£��������������أ��ǵմ����Ӳ�����\n");
			return 1;
		}
        if (ob->query("thdjj/ronghe")=="pass") {
                command("say �㲻���Ѿ�ѧ������");
				ob->set("title",HIM"�һ���"+HIG"��а����"NOR);
				ob->set("mytitle/quest/thdrhtitle",HIM"�һ���"+HIG"��а����"NOR);
                return 1;
        }
        if (ob->query("age") < 14) {
                command("say Ҫʹ�������ľ�����Ҫ�������㻹�ǵȳ���Щ��˵�ɡ�");
                return 1;
        }

//����title
        if (ob->query_skill("bihai-chaosheng",1) < 500) {
                command("say Ҫʹ�������ľ�����Ҫ������ڹ����㻹�Ƕ���ϰ��ϰ���̺�����������˵�ɡ�");
                return 1;
        }
		if (ob->query_skill("yuxiao-jian",1) < 500) {
                command("say Ҫʹ�������ľ�����Ҫ��������｣�����㻹�Ƕ���ϰ��ϰ���̺�����������˵�ɡ�");
                return 1;
        }

		if (ob->query("int") < 40) {
                command("say Ҫʹ�������ľ�����Ҫ�ܺõ��������ԣ�40�����㻹�ǵȳ���Щ��˵�ɡ�");
                return 1;
        }
         time=time() - (int)ob->query("thdjj/ronghe/time");
		if(ob->query("thdjj/ronghe/time") && time <86400)		
   		{
				command("say �㻹��ȥ��Ϣһ�°ɡ�");
				return 1;
		}
	    //�Ѷ�ϵ��Ϊ1/15*10
	  //  j=random(20);
		write(HIC"��ҩʦ˵����������澭�����\n"NOR);
		write(HIC"��ҩʦ˵���������ú��������ž���Ҳ���Ա˴��ں���һ�𣡵��ܷ�����ͨ�Ϳ�����컯�ˡ�\n"NOR);

		j = 25;
		if(ob->query("m-card-vip")) j =  20;
		if(ob->query("y-card-vip")) j =  17;
		if(ob->query("buyvip"))     j =  15;
		j=random(j);
		i=random(ob->query("kar"));
		if (i>27 
			&& j<3
			&& random(ob->query("int"))>40)  
		 {

            write(HIY"��ҩʦ˵������ͽ��������ϸ�ˣ�\n"NOR);
            write(HIC"��ҩʦϸ�ĵ����㽲����һ�У������ڶ��һ�����ѧ�ڻ��ͨ��\n"NOR);
		    command("chat* haha "+ob->query("id"));
		    command("chat �һ���Ӣ���񽣣��̺����������");
		    command("chat ����˴��������ļ�ͽ���Ҷ�аһ�����飡�Դ˺��һ�����а�����д��˳����ˡ�");
		    command("chat ��ϲ"+ob->query("name")+"������һ����洫��");
		    log_file("quest/thdfyjueji", sprintf("%8s(%8s) ʧ��%d�κ󣬳��������һ����ռ������������jȡֵ��%d|�����Դiȡֵ��%d|���飺%d��\n", ob->name(1),ob->query("id"), ob->query("thdjj/ronghe/fail"),j,i,ob->query("combat_exp")) );
	        ob->set("title",HIM"�һ���"+HIG"��а����"NOR);
			ob->set("mytitle/quest/thdrhtitle",HIM"�һ���"+HIG"��а����"NOR);
            ob->set("thdjj/ronghe","pass"); 
	        return 1;  
		 } else {     
		    command("sigh "+ob->query("id"));
			command("say �һ����ľ������Ҫ�ںϹ�ͨ��������Ҫһ�����������㻹���´���˵�ɡ�\n");
			command("disapp "+ob->query("id"));
			ob->set("thdjj/ronghe/time",time());
			ob->add("thdjj/ronghe/fail",1);
			log_file("quest/tdhfyjueji", sprintf("%8s(%8s) �һ����ںϾ�������ʧ��%d�Ρ������jȡֵ��%d|�����Դiȡֵ��%d|���飺%d��\n", ob->name(1),ob->query("id"), ob->query("thdjj/ronghe/fail"),j,i,ob->query("combat_exp")) );
			return 1;
		 }
}	

int ask_lhssjj()
{
        int i,j,time;
		object ob = this_player();
        
        
        if (ob->query("family/family_name") != "�һ���"||ob->query("family/master_name")!="��ҩʦ") {
                command("say �������ǼҴ���ѧ�������ʲô��");
                return 1;
        }
		if (!ob->query("quest/thd/dichuan"))
		{
			command("say ����Ȼ�������е��ӣ���Ϊ�һ�������ʲô�ȣ�\n");
			command("say �Ҷ�а���£��������������أ��ǵմ����Ӳ�����\n");
			return 1;
		}
        if (ob->query("quest/thd/lhs/lanhua/pass")) {
                command("say �㲻���Ѿ�ѧ������");
                ob->set("title",HIM"�һ���"+HIC"�����ִ���"NOR);
				ob->set("mytitle/quest/thdlhstitle",HIM"�һ���"+HIC"�����ִ���"NOR);
                return 1;
        }
        if (ob->query("age") < 14) {
                command("say Ҫʹ�������ľ�����Ҫ�������㻹�ǵȳ���Щ��˵�ɡ�");
                return 1;
        }
		
//����title
        if (ob->query_skill("bihai-chaosheng",1) < 500) {
                command("say Ҫʹ�������ľ�����Ҫ������ڹ����㻹�Ƕ���ϰ��ϰ���̺�����������˵�ɡ�");
                return 1;
        }
		if (ob->query("str") < 40) {
                command("say Ҫʹ�������ľ�����Ҫ�ܺõ����������40�����㻹�ǵȳ���Щ��˵�ɡ�");
                return 1;
        }
        time=time() - (int)ob->query("quest/thd/lhs/lanhua/time");
		if(ob->query("quest/thd/lhs/lanhua/time") && time<86400)		
   		{
				command("say �㻹��ȥ��Ϣһ�°ɡ�");
				return 1;
		}
	    //�Ѷ�ϵ��Ϊ1/15*10
	  //  j=random(20);
		write(HIC"��ҩʦ˵�������������������һ����Ҵ�֮������������֮�˲��ô��ڣ�\n"NOR);
		write(HIC"��ҩʦ˵������Ȼ��������������Ҿͽ�����ʽ�������㣡�ܷ�����ͨ�Ϳ�����컯�ˡ�\n"NOR);

		j = 25;
		if(ob->query("m-card-vip")) j =  20;
		if(ob->query("y-card-vip")) j =  17;
		if(ob->query("buyvip"))     j =  15;
		j=random(j);
		i=random(ob->query("kar"));
		if (i>26 
			&& j<3
			&& random(ob->query("str"))>40)  
		 {

            write(HIR"��ҩʦϸ�ĵ����㽲����һ�У������ڶ��һ����Ҵ���ѧ������ʽ�ڻ��ͨ��\n"NOR);
		    command("chat* haha "+ob->query("id"));
		    command("chat ��ʮ��������ҹ��˭֪���������㡣");
		    command("chat ����˴��������ļ�ͽ���Ҷ�аһ�����飡�Դ˺��һ��������������д��˳����ˡ�");
		    command("chat ��ϲ"+ob->query("name")+"������һ��������־����洫��");
		    log_file("quest/thdlhsjueji", sprintf("%8s(%8s) ʧ��%d�κ󣬳��������һ����������ռ������������jȡֵ��%d|�����Դiȡֵ��%d|���飺%d��\n", ob->name(1),ob->query("id"), ob->query("quest/thd/lhs/lanhua/fail"),j,i,ob->query("combat_exp")) );
	        ob->set("title",HIM"�һ���"+HIC"�����ִ���"NOR);
			ob->set("mytitle/quest/thdlhstitle",HIM"�һ���"+HIC"�����ִ���"NOR);
            ob->set("quest/thd/lhs/lanhua/pass",1); 
	        return 1;  
		 } else {     
		    command("sigh "+ob->query("id"));
			command("say �һ������������Ǻ��������������ء�\n");

			command("say �һ��������������ǼҴ���������һʱ�������ˣ�Ҳ�е���Ϊ���ˣ�������Ҫһ�����������㻹���´���˵�ɡ�\n");
			command("disapp "+ob->query("id"));
			ob->set("quest/thd/lhs/lanhua/time",time());
			ob->add("quest/thd/lhs/lanhua/fail",1);
			log_file("quest/thdlhsjueji", sprintf("%8s(%8s) �һ��������־�������ʧ��%d�Ρ������jȡֵ��%d|�����Դiȡֵ��%d|���飺%d��\n", ob->name(1),ob->query("id"),ob->query("quest/thd/lhs/lanhua/fail"),j,i,ob->query("combat_exp")) );
	        return 1;
		 }
}	