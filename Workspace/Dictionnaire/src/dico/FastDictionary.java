package dico;

public class FastDictionary extends AbstractDictionary
{

	public FastDictionary()
	{
		this.taille=1;
		this.key=new Object[this.taille];
		this.value=new Object[this.taille];
	}

	public FastDictionary(int p_taille)
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
		int index = p_key.hashCode()%this.taille;
		if (index<0)
		{
			index =index * -1;
		}
		
		if (this.key[index]!=p_key)
		{	
			int i = index;
            do
            {
                i++;
                if(i == this.taille)
                {
                    i = 0;
                }//it will stop with i==index
            }while((i != index) && (this.key[i] != p_key));
            
            if(i == index)
            {
            	//System.out.println("La valeur "+p_key+" n'existe pas");
                return existe;
            }
            else
            {
                return i;
            }
		}
		else
		{
			return index;
		}
	}

	@Override
	int newIndexOf(Object p_key) 
	{
		// TODO Auto-generated method stub
		/*return -1 if there is already the key
		 * else return the index the new key 
		 * will be inserted.
		 */
		if (this.mustGrow())
		{
			this.grow();
			System.out.println("Je suis agrandi");
		}
		
		if (this.indexOf(p_key)!=-1)
		{
			return -1;//there is already a key
		}
		else
		{
			int i = p_key.hashCode() % taille;
            if(i<0)
            {
                i = i * -1;
            }
			while (this.key[i]!=null)
			{//searching a new place available
				i++;
				if (i==this.taille)
				{
					i=0;
				}
			}
			//System.out.println(i);
			return i;
		}
		
	}
	
	boolean mustGrow()
	{
		/*return true when arrays are full at 3/4
		 * else false
		 */
		return (((float)this.size()/(float)this.taille)>0.75);
	}
	
	void grow()
	{
		/*grow if arrays is full at 3/4
		 * 
		 */
		Object[] key_temp;
		Object[] value_temp;
		key_temp=new Object[this.taille];
		value_temp=new Object[this.taille];
		
		for (int i=0;i<this.taille;i++)
		{
			key_temp[i]=this.key[i];
			value_temp[i]=this.value[i];
			//we obtain a free place in temporaries
		}
		
		key=new Object[this.taille+1];
		value=new Object[this.taille+1];
		//Must recalculate hash code with new modulo (size has changed)
		
		for (int i=0;i<this.taille;i++)
		{
			Object key=key_temp[i];
			Object value=value_temp[i];
			
			int index = key.hashCode()%this.taille;
			if (index<0)
			{
				index =index * -1;
			}
			
			int code=index;//new hash code with modulo
			this.key[code]=key;
			this.value[code]=value;
		}
		//arrays has grew of size plus one
		this.taille++;//update of the size
	}

}
