<?php
//$Id$

/**
 * @file xero-invoice.tpl.php
 * 
 * Available variables:
 * - $invoice: the raw array structure for an invoice.
 * - $currency: the currency code used for this invoice (e.g.: USD).
 * - $type: the type of invoice: accrec or accpay.
 * - $status: the status of the invoice: drafted, submitted, accepted, etc...
 * - $invoiceid: the raw invoiceid for this invoice.
 * - $number: the sanitized invoice number.
 * - $name: the contact name associated with the invoice
 * - $contactid: the raw contactid for this invoice.
 * - $date: the timestamp the invoice was submiitted.
 * - $duedate: the timestamp the invoice is due.
 * - $total: the total amount on the invoice
 * - $paid: the total amount paid on the invoice.
 * - $due: the total amount due on the invoice.
 * - $credited: the amount credited.
 * - $lineamounttypes: the line amount type
 * - $lineitems: an array of line items to be themed
 * - $payments: table of payments, if any.
 *
 * @see template_preprocess_xero_invoice().
 */
?>
<div class="xero-invoice xero-invoice-<?php print $type; ?>">
  <h2 class="title"><?php print $number; ?></h2>

  <div class="submitted">
    <span class="date">Submitted on <?php print format_date($date, 'short'); ?></span><br />
    <span class="date">Due on <?php print format_date($duedate, 'short'); ?></span>
  </div>

  <div class="summary">
    <?php if ($currency <> '') : ?>
    <p><span class="currency">All currencies are <?php print $currency; ?></span></p>
    <?php endif; ?>
    <span class="total">Total Amount: <?php print $total; ?></span><br />
    <span class="paid">Total Paid: <?php print $paid; ?></span><br />
    <span class="due">Total Due: <?php print $due; ?></span><br />
    <span class="status">Status: <?php print $status; ?></span>
  </div>

  <?php if (!empty($lineitems)) : ?>
  <div class="line-items-wrapper">
    <?php print theme('xero_lineitems', $lineitems, $invoice['SubTotal'], $invoice['TotalTax'], $total); ?>
  </div>
  <?php endif; ?>

  <?php if ($payments <> '') : ?>
  <div class="payments-wrapper">
    <?php print $payments; ?>
  </div>
  <?php endif; ?>

</div>
