ki_to_ki=float(1.0)
po_to_ki=float(0.453592)
st_to_ki=float(6.35029)
ji_to_ki=float(0.5)
se_to_ki=float(1.25)
gr_to_ki=float(0.001)
ok_to_ki=float(1.2829)
#"these are coefficients used to convert mass from the current unit to the target unit, for instance, if we multiple the mass in the current unit by this coefffient, we will get the mass in kilograms; likewise, if we divide the mass in kilograms of the of coefficient, we will get the mass in the corresponding unit"

def convert_mass(value,current,target):
    '''
    converting mass from kilogram to the target unit
    '''
    if current=="Kilogram": 
        if target=="Kilogram":
            mass=value
            return(float(mass))
        elif target=="Pound":
            mass=value/po_to_ki
            return(float(mass))
        elif target=="Stone":
            mass=value/st_to_ki
            return(float(mass))
        elif target=="Jin":
            mass=value/ji_to_ki
            return(float(mass))
        elif target=="Seer":
            mass=value/se_to_ki
            return(float(mass))
        elif target=="Gram":
            mass=value/gr_to_ki
            return(float(mass))
        elif target=="Oka":
            mass=value/ok_to_ki
            return(float(mass))
        else:
            return 0 #"indicate the user has input an invalid target unit"
  
    elif current=="Pound": #"converting mass from pound to the target unit"
        mass_in_ki=value*po_to_ki #"converting mass from pound to kilogram for further process"
        if target=="Kilogram":
            mass=mass_in_ki
            return(float(mass))
        elif target=="Pound":
            mass=value
            return(float(mass))
        elif target=="Stone":
            mass=mass_in_ki/st_to_ki
            return(float(mass))
        elif target=="Jin":
            mass=mass_in_ki/ji_to_ki
            return(float(mass))
        elif target=="Seer":
            mass=mass_in_ki/se_to_ki
            return(float(mass))
        elif target=="Gram":
            mass=mass_in_ki/gr_to_ki
            return(float(mass))
        elif target=="Oka":
            mass=mass_in_ki/ok_to_ki
            return(float(mass))
        else:
            return 0
   
    elif current=="Stone": #"converting mass from stone to the target unit"
        mass_in_ki=value*st_to_ki
        if target=="Kilogram":
            mass=mass_in_ki
            return(float(mass))
        elif target=="Pound":
            mass=mass_in_ki/po_to_ki
            return(float(mass))
        elif target=="Stone":
            mass=value
            return(float(mass))
        elif target=="Jin":
            mass=mass_in_ki/ji_to_ki
            return(float(mass))
        elif target=="Seer":
            mass=mass_in_ki/se_to_ki
            return(float(mass))
        elif target=="Gram":
            mass=mass_in_ki/gr_to_ki
            return(float(mass))
        elif target=="Oka":
            mass=mass_in_ki/ok_to_ki
            return(float(mass))
        else:
            return 0
            
    elif current=="Jin": #"converting mass from jin to the target unit"
        mass_in_ki=value*ji_to_ki
        if target=="Kilogram":
            mass=mass_in_ki
            return(float(mass))
        elif target=="Pound":
            mass=mass_in_ki/po_to_ki
            return(float(mass))
        elif target=="Stone":
            mass=mass_in_ki/st_to_ki
            return(float(mass))
        elif target=="Jin":
            mass=value
            return(float(mass))
        elif target=="Seer":
            mass=mass_in_ki/se_to_ki
            return(float(mass))
        elif target=="Gram":
            mass=mass_in_ki/gr_to_ki
            return(float(mass))
        elif target=="Oka":
            mass=mass_in_ki/ok_to_ki
            return(float(mass))
        else:
            return 0
    
    elif current=="Seer": #"converting mass from seer to the target unit"
        mass_in_ki=value*se_to_ki
        if target=="Kilogram":
            mass=mass_in_ki
            return(float(mass))
        elif target=="Pound":
            mass=mass_in_ki/po_to_ki
            return(float(mass))
        elif target=="Stone":
            mass=mass_in_ki/st_to_ki
            return(float(mass))
        elif target=="Jin":
            mass=mass_in_ki/ji_to_ki
            return(float(mass))
        elif target=="Seer":
            mass=value
            return(float(mass))
        elif target=="Gram":
            mass=mass_in_ki/gr_to_ki
            return(float(mass))
        elif target=="Oka":
            mass=mass_in_ki/ok_to_ki
            return(float(mass))
        else:
            return 0
    
    elif current=="Gram": #"converting mass from gram to the target unit"
        mass_in_ki=value*gr_to_ki
        if target=="Kilogram":
            mass=mass_in_ki
            return(float(mass))
        elif target=="Pound":
            mass=mass_in_ki/po_to_ki
            return(float(mass))
        elif target=="Stone":
            mass=mass_in_ki/st_to_ki
            return(float(mass))
        elif target=="Jin":
            mass=mass_in_ki/ji_to_ki
            return(float(mass))
        elif target=="Seer":
            mass=mass_in_ki/se_to_ki
            return(float(mass))
        elif target=="Gram":
            mass=value
            return(float(mass))
        elif target=="Oka":
            mass=mass_in_ki/ok_to_ki
            return(float(mass))
        else:
            return 0
    
    elif current=="Oka": #"converting mass from Oka to the target unit"
        mass_in_ki=value*ok_to_ki
        if target=="Kilogram":
            mass=mass_in_ki
            return(float(mass))
        elif target=="Pound":
            mass=mass_in_ki/po_to_ki
            return(float(mass))
        elif target=="Stone":
            mass=mass_in_ki/st_to_ki
            return(float(mass))
        elif target=="Jin":
            mass=mass_in_ki/ji_to_ki
            return(float(mass))
        elif target=="Seer":
            mass=mass_in_ki/se_to_ki
            return(float(mass))
        elif target=="Gram":
            mass=mass_in_ki/gr_to_ki
            return(float(mass))
        elif target=="Oka":
            mass=value
            return(float(mass))
        else:
            return 0
    
    else:
        return 0 #"indicate the user has input a wrong current unit"
