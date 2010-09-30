<?php
//$Id$

/**
 * @file
 * 
 */


/**
 * Xero Make Contact callback. Makes an empty contact.
 * @param $size minimal or all
 * @param $address number of address data structures to make.
 * @param $phone number of phone data structures to make.
 * @return an empty contact data structure.
 */
function xero_make_contact($size = 'minimal', $address = 0, $phone = 0) {
  //Minimal
  $contact = array(
    'Contact' => array(
      'Name' => '',
    ),
  );

  if ($size == 'minimal') {
    return $contact;
  }

  $keys = array('FirstName', 'LastName', 'EmailAddress', 'BankAccountDetails', 'TaxNumber', 'AccountsReceivableTaxType', 'AccountsPayableTaxType', 'ContactGroups', 'IsSupplier', 'IsCustomer', 'DefaultCurrency');

  foreach ($keys as $key) {
    $contact['Contact'][$key] = '';
  }

  while ($address > 0) {
    if (!isset($contact['Contact']['Addresses'])) {
      $contact['Contact']['Addresses'] = array();
    }
    $contact['Contact']['Addresses'][] = xero_make_address('all', 4);
    $address--;
  }

  while ($phone > 0) { 
    if (!isset($contact['Contact']['Phones'])) {
      $contact['Contact']['Phones'] = array();
    }
    $contact['Contact']['Phones'][] = xero_make_phone('all');
    $phone--;
  }

  return $contact;
}

/**
 * Xero Make Address callback.
 * @param $size minimal or all
 * @param $lines the number of address lines to use. Default to 1.
 * @return a valid address data structure
 */
function xero_make_address($size = 'minimal', $lines = 1) {
  $address = array(
    'Address' => array(
      'AddressType' => '',
    ),
  );

  if ($size == 'minimal') {
    return $address;
  }

  $keys = array('City', 'Region', 'PostalCode', 'CountryCode');

  for ($i = 1; $i <= 4; $i++) {
    $address['Address']['AddressLine' . $i] = '';
  }

  foreach ($keys as $key) {
    $address['Address'][$key] = '';
  }

  return $address;
}

/**
 * Xero Make Phone callback.
 * @param $size minimal or all
 * @return a valid phone data structure
 */
function xero_make_phone($size = 'minimal') {
  $phone = array(
    'Phone' => array(
      'PhoneType' => '',
    ),
  );

  if ($size == 'minimal') {
    return $phone;
  }

  $keys = array('PhoneNumber', 'PhoneAreaCode', 'PhoneCountryCode');
 
  foreach ($keys as $key) {
    $phone['Phone'][$key] = '';
  }

  return $phone;
}

/**
 * Xero Make Payment callback
 * @param $size minimal
 * @param $invid whether to use id or number for invoice
 * @param $accid whether to use id or code for account
 * @return a valid payment data structure
 */
function xero_make_payment($size = 'minimal', $invid = 'id', $accid = 'id') {
  $payment = array(
    'Payment' => array(
      'Date' => '',
      'Amount' => '',
      'Invoice' => array(),
      'Account' => array(),
    ),
  );

  if ($invid == 'id') {
    $payment['Payment']['Invoice']['InvoiceID'] = '';
  }
  else {
    $payment['Payment']['Invoice']['InvoiceNumber'] = '';
  }

  if ($accid == 'id') {
    $payment['Payment']['Account']['AccountID'] = '';
  }
  else {
    $payment['Payment']['Account']['Code'] = '';
  }

  return $payment;
}

/**
 * Xero Make Invoice callback
 * @param $size minimal, recommended, all
 * @param $contact_type whether to set contact id or name
 * @param $items number of line items to generate
 * @return a valid invoice data structure.
 */
function xero_make_invoice($size = 'minimal', $contact_type = 'id', $items = 1) {
  $invoice = array(
    'Invoice' => array(
      'Type' => '',
      'Contact' => array(),
    ),
  );

  if ($contact_type == 'id') {
    $invoice['Invoice']['Contact']['ContactID'] = '';
  }
  else {
    $invoice['Invoice']['Contact']['Name'] = '';
  }

  if ($size == 'minimal') {
    return $invoice;
  }

  $keys = array('Date', 'DueDate', 'LineAmountTypes', 'LineItems');
  
  if ($size == 'all') {
    $keys = array_merge($keys, array('InvoiceNumber', 'Reference', 'CurrencyCode', 'Status', 'SubTotal', 'TotalTax', 'Total'));
  }

  foreach ($keys as $key) {
    if ($key == 'LineItems') {
      $invoice['Invoice']['LineItems'] = array();
      for ($i = 0; $i < $items; $i++) {
        $invoice['Invoice']['LineItems'][] = xero_make_lineitem($size);
      }
    }
    else {
      $invoice['Invoice'][$key] = '';
    }
  }

  return $invoice;
}

/**
 * Xero Make Credit Note callback
 * @param $size minimal, recommended, all
 * @param $contact_type id or name
 * @param $items the number of line items to create.
 * @retutrn a valid Credit Note data structure.
 */
function xero_make_creditnote($size = 'minimal', $contact_type = 'id', $items = 1) {
  $cn = array(
    'CreditNote' => array(
      'Type' => '',
      'Contact' => array(),
    ),
  );

  if ($contact_type == 'id') {
    $cn['CreditNote']['Contact']['ContactID'] = '';
  }
  else {
    $cn['CreditNote']['Contact']['Name'] = '';
  }

  if ($size == 'minimal') {
    return $cn;
  }

  $keys = array('Date', 'DueDate', 'LineAmountTypes', 'LineItems');
  
  if ($size == 'all') {
    $keys = array_merge($keys, array('CreditNoteNumber', 'Reference', 'CurrencyCode', 'Status', 'SubTotal', 'TotalTax', 'Total'));
  }

  foreach ($keys as $key) {
    if ($key == 'LineItems') {
      $invoice['Invoice']['LineItems'] = array();
      for ($i = 0; $i < $items; $i++) {
        $invoice['Invoice']['LineItems'][] = xero_make_lineitem($size);
      }
    }
    else {
      $invoice['Invoice'][$key] = '';
    }
  }

  return $cn;
}

/**
 * Xero Make Line Item callback
 * @param $size minimal, recommended, or all
 * @return a valid lineitem data structure
 */
function xero_make_lineitem($size = 'minimal') {
  $lineitem = array(
    'LineItem' => array(),
  );

  if ($size == 'minimal') {
    return $lineitem;
  }

  $keys = array('Description', 'Quantity', 'UnitAmount', 'AccountCode');

  if ($size == 'all') {
    $keys = array_merge($keys, array('TaxType', 'TaxAmount', 'LineAmount', 'Tracking'));
  }

  foreach ($keys as $key) {
    if ($key == 'Tracking') {
      $lineitem['LineItem'][$key] = array();
      //$lineitem['LineItem'][$key][] = xero_make_tracking($size);
      //$lineitem['LineItem'][$key][] = xero_make_tracking($size);
    }
    else {
      $lineitem['LineItem'][$key] = '';
    }
  }

  return $lineitem;
}
