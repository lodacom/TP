package dico;

public class OrderedDictionary extends AbstractDictionary
{
	
	public OrderedDictionary()
	{
		this.taille=1;
		this.key=new Object[this.taille];
		this.value=new Object[this.taille];
	}
	
	public OrderedDictionary(int p_taille)
	{
		this.taille=p_taille;
		this.key=new Object[this.taille];
		this.value=new Object[this.taille];
	}
	
	@Override
	int indexOf(Object p_key) 
	{
		// TODO Auto-generated method stub
		/*return -1 if the key doesn't exist in the dictionary
		 * else return the index
		*/
		int existe=-1;
		int i=0;
		while (i<this.taille && this.key[i]!=p_key)
		{
			i++;
		}
		if (i<this.taille)
		{
			existe=i;
		}
		return existe;
	}

	@Override
	int newIndexOf(Object key) 
	{
		// TODO Auto-generated method stub
		/*return -1 if there is already the key
		 * else return the new size. Thus a new key 
		 * will be inserted.
		 */
		if (this.indexOf(key)==-1)
		{
			if (this.size()==this.taille)
			{
				System.out.println("Le nombre d'ŽlŽment est Žgal ˆ la taille"+this.size()+" "+this.taille);
				Object[] key_temp;
				Object[] value_temp;
				
				key_temp=new Object[this.taille+1];
				value_temp=new Object[this.taille+1];
				
				for (int i=0;i<this.taille;i++)
				{
					key_temp[i]=this.key[i];
					value_temp[i]=this.value[i];
					//we obtain a free place in temporaries
				}
				
				this.taille++;//update of size
				this.key=new Object[this.taille];
				this.key=key_temp.clone();//clone of key_temp in this.key with new size
				this.value=new Object[this.taille];
				this.value=value_temp.clone();
				
				return this.taille;
			}
			else
			{
				int i=0;
				while (i<this.taille && this.key[i]!=null)
				{
					i++;
				}
				if(i<this.taille)
				{
					return i;
				}
				else
				{
					return this.taille;
				}
			}
			
		}
		else
		{
			return -1;
		}
		
	}
}
