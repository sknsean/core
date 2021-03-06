import oelite.fetch.fetch
from oelite.fetch.sigfile import SignatureFile
from oelite.fetch.fetch import *

class FetchException(Exception):
    def __init__(self, uri, msg):
        self.uri = uri
        self.message = msg
        return

    def __str__(self):
        return "%s: %s: %s"%(self.prefix, self.message, self.uri)


class InvalidURI(FetchException):
    """Exception raised when parsing an invalid URI"""
    prefix = "Invalid URI"

class LocalFileNotFound(FetchException):
    """Exception raised when local URI file is not found"""
    prefix = "No file found for local URI"

class FetchError(FetchException):
    """Exception raised when failing to fetch file"""
    prefix = "Fetch failed"

class NoSignature(FetchException):
    """Exception raised when signature of file to be fetched is not known"""
    prefix = "No checksum"

class ChecksumError(FetchException):
    """Exception raised when checksum of fetched file does not match"""
    prefix = "Bad checksum"

class ParameterError(FetchException):
    """Exception raised when parsed URI parameter is invalid"""
    prefix = "Invalid parameter"


__all__ = [
    "OEliteUri",
    "FetchException",
    "InvalidURI", "FetchError", "ChecksumError", "ParameterError",
    "SignatureFile",
    ]
