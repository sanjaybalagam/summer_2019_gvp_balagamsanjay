from assign4.p1.p2 import m2
from assign4.p1 import m1
from assign4.p1.p3 import m3
import logging
import logging.config


def configure_logging():
    CUSTOM_LOGGING  = {
        'version' : 1,
        'disable_existing_loggers': False,
        'loggers' : {
            '' : {
                'handlers': ['console', 'main.log'],
                'level': "DEBUG",
            },
            'p1.p2' : {
                'handlers': ['p2.log', 'console'],
                'level': "DEBUG",
                'propagate': False
            },
            'p1': {
                'handlers': ['p1.log'],
                'level': "DEBUG",
                'propagate': False
            },
        },
        'handlers' : {
            'console': {
                'level': 'WARNING',
                'class': 'logging.StreamHandler',
                'stream': 'ext://sys.stderr'
            },
            'p2.log': {
                'class': 'logging.FileHandler',
                'filename': 'p2.log'
            },

            'p1.log': {
                'class': 'logging.FileHandler',
                'filename': 'p1.log'
            },

            'main.log': {
                'class': 'logging.FileHandler',
                'filename': 'main.log'
            }
        }
    }
    logging.config.dictConfig(CUSTOM_LOGGING)

logger =logging.getLogger('main')

if __name__ == '__main__':
    logger=logging.getLogger('')
    configure_logging()
    m1.f1()
    m1.f2()
    m2.f3()
    m3.f4()
    logging.info('main info msg')
    logging.warning('main WARNING msg')
    logging.error('main ERROR msg')
    logging.critical('main CRITICAL msg')

