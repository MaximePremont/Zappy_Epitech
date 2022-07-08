import logging

def safe_cast(val, to_type: type):
    """a utils function that cast a value to a given type and exit the program
    if the cast fails.

    Args:
        val (_type_): the value to be cast
        to_type (type): the type of the cast

    Returns:
        type: the casted value 
    """
    try:
        return to_type(val)
    except:
        print(val)
        logging.CRITICAL("Safe cast failed")